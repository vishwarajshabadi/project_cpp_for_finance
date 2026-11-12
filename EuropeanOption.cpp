#include "EuropeanOption.h"
#include <stdexcept>

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike)
{
    if (expiry < 0.0 || strike < 0.0)
        throw std::invalid_argument("Expiry and strike must be nonnegative");
}

double EuropeanVanillaOption::getStrike() const {
    return _strike;
}