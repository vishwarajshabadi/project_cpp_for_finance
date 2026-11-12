#include "Option.h"
#include <stdexcept>

Option::Option(double expiry) : _expiry(expiry) {
    if (expiry < 0.0)
        throw std::invalid_argument("Expiry must be non-negative");
}

double Option::getExpiry() const {
    return _expiry;
}

