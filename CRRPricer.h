#pragma once
#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {
public:
    CRRPricer(Option* option, int depth, double asset_price,
        double up, double down, double interest_rate);

    void compute();                                   // procédure CRR (récurrence arrière)
    double get(int n, int i);                         // H(n, i)
    double operator()(bool closed_form = false);      // prix H(0, 0)

private:
    Option* _option;
    int _depth;            // N
    double _asset_price;   // S0
    double _up;            // U
    double _down;          // D
    double _interest_rate; // R
    BinaryTree<double> _tree;   // stocke H(n, i)
    bool _computed;             // compute() a-t-il déjà été appelé ?

    double riskNeutralProbability() const;   // q = (R - D) / (U - D)
    double stockPrice(int n, int i) const;   // S(n, i) = S0 (1+U)^i (1+D)^(n-i)
};