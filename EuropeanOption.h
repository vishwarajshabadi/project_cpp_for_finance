#pragma once
#include "Option.h"
#include <stdexcept>

class EuropeanVanillaOption : public Option {
public:
    EuropeanVanillaOption(double expiry, double strike)
        : Option(expiry), _strike(strike)
    {
        if (expiry < 0.0 || strike < 0.0)
            throw std::invalid_argument("Expiry and strike must be nonnegative");
    }

    virtual optionType GetOptionType() const = 0;   // virtuelle pure

    double getStrike() const { return _strike; }    // ajout : nécessaire pour les payoffs

private:
    double _strike;
};
class OptionCall{
    public :
    
}