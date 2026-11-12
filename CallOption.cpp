#include "CallOption.h"

CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}

double CallOption::payoff(double z) const {
    return (z >= getStrike()) ? z - getStrike() : 0.0;
}

optionType CallOption::GetOptionType() const {
    return optionType::call;
}
