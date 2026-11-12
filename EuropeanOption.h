#pragma once
#include "Option.h"

class BlackScholesPricer;   // avant-declaration pour l'ami (spec Part I, question 4)

enum class optionType { call, put };

class EuropeanVanillaOption : public Option {
public:
    EuropeanVanillaOption(double expiry, double strike);

    virtual optionType GetOptionType() const = 0;   // virtuelle pure

    friend class BlackScholesPricer;   // le pricer lit le strike directement

protected:
    double getStrike() const;   // accessor pour les classes derivees (payoff Call/Put)

private:
    double _strike;
};