#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price,
    double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price),
    _up(up), _down(down), _interest_rate(interest_rate),
    _tree(depth), _computed(false) {
    if (!option)          throw std::invalid_argument("CRRPricer : option nulle");
    if (depth < 0)        throw std::invalid_argument("CRRPricer : depth doit etre >= 0");
    if (asset_price <= 0) throw std::invalid_argument("CRRPricer : S0 doit etre > 0");
    if (down <= -1)       throw std::invalid_argument("CRRPricer : il faut D > -1");
    // Absence d'arbitrage : D < R < U
    if (!(down < interest_rate && interest_rate < up))
        throw std::invalid_argument("CRRPricer : arbitrage possible, il faut D < R < U");
}

double CRRPricer::riskNeutralProbability() const {
    return (_interest_rate - _down) / (_up - _down);
}

double CRRPricer::stockPrice(int n, int i) const {
    return _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, n - i);
}

void CRRPricer::compute() {
    const double q = riskNeutralProbability();

    // À l'échéance N : H(N, i) = h(S(N, i))
    for (int i = 0; i <= _depth; ++i)
        _tree.setNode(_depth, i, _option->payoff(stockPrice(_depth, i)));

    // Récurrence arrière : H(n, i) = [q H(n+1, i+1) + (1-q) H(n+1, i)] / (1+R)
    for (int n = _depth - 1; n >= 0; --n)
        for (int i = 0; i <= n; ++i)
            _tree.setNode(n, i, (q * _tree.getNode(n + 1, i + 1)
                + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate));

    _computed = true;
}

double CRRPricer::get(int n, int i) {
    if (!_computed) compute();
    return _tree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) {
    if (!closed_form) {
        if (!_computed) compute();
        return _tree.getNode(0, 0);
    }

    // Formule fermée : H(0,0) = 1/(1+R)^N * somme_i C(N,i) q^i (1-q)^(N-i) h(S(N,i))
    // C(N,i) q^i (1-q)^(N-i) est calculé via les logarithmes (lgamma) pour éviter
    // le dépassement de capacité de N! quand N est grand.
    const double q = riskNeutralProbability();
    const int N = _depth;
    double somme = 0.0;
    for (int i = 0; i <= N; ++i) {
        double logPoids = std::lgamma(N + 1.0) - std::lgamma(i + 1.0) - std::lgamma(N - i + 1.0);
        if (i > 0)     logPoids += i * std::log(q);
        if (N - i > 0) logPoids += (N - i) * std::log(1 - q);
        somme += std::exp(logPoids) * _option->payoff(stockPrice(N, i));
    }
    return somme / std::pow(1 + _interest_rate, N);
}