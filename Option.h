#pragma once

class Option {
public:
    explicit Option(double expiry);
    virtual ~Option() = default;          // indispensable pour une classe de base polymorphe

    double getExpiry() const;

    // Fonction de payoff h(S), à définir dans les classes dérivées
    virtual double payoff(double S) const = 0;

private:
    double _expiry;
};
