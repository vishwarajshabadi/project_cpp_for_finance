#pragma once
#include "Option.h"
#include "BinaryTree.h"


class CRRPricer {
public:

    CRRPricer(Option* option, int depth, double asset_price,
        double up, double down, double interest_rate);

    // Remplit l'arbre des valeurs de l'option H(n, i)
    void compute();

    // Renvoie H(n, i), la valeur de l'option au noeud (n, i)
    double get(int n, int i);

 
    double operator()(bool closed_form = false);

private:
    // Outils de calcul internes
    double riskNeutralProbability() const;   // q = (R - D) / (U - D)
    double stockPrice(int n, int i) const;   // S(n, i) = S0 (1+U)^i (1+D)^(n-i)
    double factorielle(int n) const;         // n! = 1 x 2 x ... x n

    // Attributs (declares dans le meme ordre que la liste d'initialisation)
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    BinaryTree<double> _tree;   // _tree[n][i] = H(n, i)
    bool _computed;             // vrai une fois l'arbre calcule
};
