#ifndef PUTOPTION_H
#define PUTOPTION_H

#include "EuropeanOption.h"

// European put option (Part I, question 3).
class PutOption : public EuropeanVanillaOption {
public:
    PutOption(double expiry, double strike);
    double payoff(double z) const override;
    optionType GetOptionType() const override;
};

#endif
