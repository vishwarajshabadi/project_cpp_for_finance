#include "EuropeanDigitalOption.h"

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalCallOption::payoff(double z) const {
    return (z >= getStrike()) ? 1.0 : 0.0;
}

optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::call;
}

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalPutOption::payoff(double z) const {
    return (z <= getStrike()) ? 1.0 : 0.0;
}

optionType EuropeanDigitalPutOption::GetOptionType() const {
    return optionType::put;
}
