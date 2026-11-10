#include "BlackScholesPricer.h"

#include <cmath>
#include <stdexcept>

// Standard normal CDF via erfc.
namespace {
double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}
}  // namespace

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option,
                                       double asset_price,
                                       double interest_rate,
                                       double volatility)
    : _option(option),
      _asset_price(asset_price),
      _interest_rate(interest_rate),
      _volatility(volatility) {
    if (asset_price <= 0 || volatility <= 0) {
        throw std::invalid_argument("asset price and volatility must be positive");
    }
}

double BlackScholesPricer::operator()() const {
    const double K = _option->_strike;   // acces friend
    const double T = _option->getExpiry();
    const double S = _asset_price;
    const double r = _interest_rate;
    const double sigma = _volatility;

    const double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    const double d2 = d1 - sigma * std::sqrt(T);

    if (_option->GetOptionType() == optionType::call) {
        return S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
    }
    return K * std::exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
}

double BlackScholesPricer::delta() const {
    const double K = _option->_strike;   // acces friend
    const double T = _option->getExpiry();
    const double S = _asset_price;
    const double r = _interest_rate;
    const double sigma = _volatility;

    const double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

    if (_option->GetOptionType() == optionType::call) {
        return norm_cdf(d1);
    }
    return norm_cdf(d1) - 1.0;
}
