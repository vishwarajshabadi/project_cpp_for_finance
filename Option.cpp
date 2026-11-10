#include <iostream>
#include <stdexcept>
#include <algorithm>

enum class OptionType
{
    Call,
    Put
};

class Option
{
public:
    explicit Option(double expiry) : _expiry(expiry)
    {
        if (expiry < 0.0)
            throw std::invalid_argument("Expiry must be non-negative");
    }
    virtual ~Option() = default;

    double getExpiry() const { return _expiry; }

    virtual double payoff(double S) const = 0; // fonction virtuelle pure

private:
    double _expiry;
};

// Classe dérivée minimale, uniquement pour tester la classe abstraite
class TestCall : public Option
{
public:
    TestCall(double expiry, double strike) : Option(expiry), _strike(strike) {}
    double payoff(double S) const override { return std::max(S - _strike, 0.0); }

private:
    double _strike;
};

int main()
{
    TestCall c(1.0, 100.0);
    std::cout << "Expiry : " << c.getExpiry() << "\n";
    std::cout << "Payoff (S=110) : " << c.payoff(110.0) << "\n"; // 10
    std::cout << "Payoff (S=90)  : " << c.payoff(90.0) << "\n";  // 0
    return 0;
}