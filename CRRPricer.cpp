#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

// Constructeur : enregistre les parametres du modele, puis verifie qu'ils sont valides
CRRPricer::CRRPricer(Option* option, int depth, double asset_price,
                     double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price),
      _up(up), _down(down), _interest_rate(interest_rate),
      _tree(depth), _computed(false)
{
    if (option == nullptr) {
        throw std::invalid_argument("CRRPricer : option nulle");
    }
    if (depth < 0) {
        throw std::invalid_argument("CRRPricer : depth doit etre >= 0");
    }
    if (asset_price <= 0) {
        throw std::invalid_argument("CRRPricer : S0 doit etre > 0");
    }
    if (down <= -1) {
        throw std::invalid_argument("CRRPricer : il faut D > -1");
    }
    // Condition d'absence d'arbitrage : D < R < U
    if (down >= interest_rate || interest_rate >= up) {
        throw std::invalid_argument("CRRPricer : arbitrage possible, il faut D < R < U");
    }
}

// Probabilite risque-neutre : q = (R - D) / (U - D)
double CRRPricer::riskNeutralProbability() const {
    return (_interest_rate - _down) / (_up - _down);
}

// Prix du sous-jacent au noeud (n, i) : S(n, i) = S0 (1+U)^i (1+D)^(n-i)
// i = nombre de hausses, n - i = nombre de baisses
double CRRPricer::stockPrice(int n, int i) const {
    return _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, n - i);
}

// Remplit l'arbre des prix de l'option H(n, i), de l'echeance vers la date 0
void CRRPricer::compute() {
    double q = riskNeutralProbability();

    // A l'echeance N : H(N, i) = h(S(N, i))
    for (int i = 0; i <= _depth; ++i) {
        double S = stockPrice(_depth, i);
        _tree.setNode(_depth, i, _option->payoff(S));
    }

    // Recurrence arriere : H(n, i) = [q H(n+1, i+1) + (1-q) H(n+1, i)] / (1+R)
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double valeurHausse = _tree.getNode(n + 1, i + 1);
            double valeurBaisse = _tree.getNode(n + 1, i);
            double valeur = (q * valeurHausse + (1 - q) * valeurBaisse) / (1 + _interest_rate);
            _tree.setNode(n, i, valeur);
        }
    }

    _computed = true;
}

// Renvoie H(n, i), en calculant l'arbre s'il ne l'a pas encore ete
double CRRPricer::get(int n, int i) {
    if (!_computed) {
        compute();
    }
    return _tree.getNode(n, i);
}

// Prix de l'option a la date 0
// closed_form = false : par l'arbre
// closed_form = true  : par la formule fermee
double CRRPricer::operator()(bool closed_form) {
    if (!closed_form) {
        if (!_computed) {
            compute();
        }
        return _tree.getNode(0, 0);
    }

    // Formule fermee :
    // H(0,0) = 1/(1+R)^N * somme sur i de C(N,i) q^i (1-q)^(N-i) h(S(N,i))
    double q = riskNeutralProbability();
    int N = _depth;
    double somme = 0.0;
    double coefBinomial = 1.0;   // C(N, 0) = 1

    for (int i = 0; i <= N; ++i) {
        double proba = coefBinomial * std::pow(q, i) * std::pow(1 - q, N - i);
        somme += proba * _option->payoff(stockPrice(N, i));

        // Passage de C(N, i) a C(N, i+1) : on multiplie par (N - i) / (i + 1)
        coefBinomial = coefBinomial * (N - i) / (i + 1);
    }

    return somme / std::pow(1 + _interest_rate, N);
}
