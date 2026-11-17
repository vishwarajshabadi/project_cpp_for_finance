#ifndef BLACKSCHOLESPRICER_H
#define BLACKSCHOLESPRICER_H

#include "EuropeanOption.h"

class EuropeanDigitalOption;   // surcharge pour les options digitales (Part II, q. 3)

// Closed-form Black-Scholes pricer for European options (Part I, question 4).
class BlackScholesPricer {
private:
    EuropeanVanillaOption* _option;
    double _asset_price;
    double _interest_rate;
    double _volatility;
    bool _digital;

public:
    BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
                       double interest_rate, double volatility);
    BlackScholesPricer(EuropeanDigitalOption* option, double asset_price,
                       double interest_rate, double volatility);
    double operator()() const;
    double delta() const;
};

#endif
