#include "CallOption.h"

// Constructeur : transmet l'echeance et le strike au constructeur de EuropeanVanillaOption,
// qui verifie qu'ils sont positifs ou nuls
CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}

// Payoff d'un call : h(z) = max(z - K, 0)
// z est le prix du sous-jacent a l'echeance
double CallOption::payoff(double z) const {
    double K = getStrike();
    if (z >= K) {
        return z - K;     // l'option est exercee : on gagne z - K
    }
    return 0.0;           // l'option n'est pas exercee : elle ne vaut rien
}

// Indique qu'il s'agit d'un call
optionType CallOption::GetOptionType() const {
    return optionType::call;
}
