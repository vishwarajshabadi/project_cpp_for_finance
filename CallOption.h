#ifndef CALLOPTION_H
#define CALLOPTION_H

#include "EuropeanOption.h"

// European call option (Part I, question 3).
class CallOption : public EuropeanVanillaOption {
public:
    CallOption(double expiry, double strike);
    double payoff(double z) const override;
    optionType GetOptionType() const override;
};

#endif
