#ifndef EUROPEANDIGITALOPTION_H
#define EUROPEANDIGITALOPTION_H

#include "EuropeanOption.h"

// European digital option (Part II, question 3).
class EuropeanDigitalOption : public EuropeanVanillaOption {
public:
    EuropeanDigitalOption(double expiry, double strike);
};

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike);
    double payoff(double z) const override;
    optionType GetOptionType() const override;
};

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike);
    double payoff(double z) const override;
    optionType GetOptionType() const override;
};

#endif
