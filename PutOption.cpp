#include "PutOption.h"

PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}

double PutOption::payoff(double z) const {
    return (z <= getStrike()) ? getStrike() - z : 0.0;
}

optionType PutOption::GetOptionType() const {
    return optionType::put;
}
