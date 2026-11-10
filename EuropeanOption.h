#pragma once
#include "Option.h"

enum class optionType { call, put };

class EuropeanVanillaOption : public Option {
public:
    EuropeanVanillaOption(double expiry, double strike);

    virtual optionType GetOptionType() const = 0;   // virtuelle pure
    double getStrike() const;

private:
    double _strike;
};

class OptionCall{
    public :

}