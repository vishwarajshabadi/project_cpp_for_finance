#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

// Arbre binaire recombinant utilise par la methode CRR.
// Le niveau n (0 <= n <= N) contient n+1 noeuds, numerotes de 0 a n.
// Comme c'est un template, tout le code est ecrit dans le .h.
template <typename T>
class BinaryTree {
private:
    int _depth;                          // N : nombre de pas de temps
    std::vector<std::vector<T>> _tree;   // _tree[n][i] : valeur du noeud i au pas n

    // Verifie que le noeud (n, i) existe dans l'arbre
    void checkIndices(int n, int i) const {
        if (n < 0 || n > _depth) {
            throw std::out_of_range("BinaryTree : n hors de l'arbre");
        }
        if (i < 0 || i > n) {
            throw std::out_of_range("BinaryTree : i hors du niveau n");
        }
    }

public:
    // Constructeur par defaut : arbre de profondeur 0 (un seul noeud)
    BinaryTree() {
        setDepth(0);
    }

    // Constructeur avec la profondeur N
    BinaryTree(int depth) {
        setDepth(depth);
    }

    // Fixe N et redimensionne l'arbre : N+1 niveaux, le niveau n ayant n+1 noeuds
    void setDepth(int depth) {
        if (depth < 0) {
            throw std::invalid_argument("BinaryTree : la profondeur doit etre >= 0");
        }
        _depth = depth;
        _tree.resize(_depth + 1);
        for (int n = 0; n <= _depth; ++n) {
            _tree[n].resize(n + 1);
        }
    }

    int getDepth() const {
        return _depth;
    }

    void setNode(int n, int i, T value) {
        checkIndices(n, i);
        _tree[n][i] = value;
    }

    T getNode(int n, int i) const {
        checkIndices(n, i);
        return _tree[n][i];
    }

    // Affiche l'arbre de deux facons
    void display() const {
        // 1) Un niveau par ligne
        for (int n = 0; n <= _depth; ++n) {
            for (int i = 0; i <= n; ++i) {
                std::cout << _tree[n][i];
                if (i < n) {                 // pas de separateur apres le dernier noeud
                    std::cout << "\t";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        // 2) Sous forme d'arbre
        // Chaque valeur occupe une case de 8 caracteres.
        // Le niveau n est decale de (N - n) demi-cases vers la droite pour etre centre.
        const int largeurCase = 8;

        for (int n = 0; n <= _depth; ++n) {
            // Decalage du niveau n
            int decalage = (_depth - n) * largeurCase / 2;

            // Ligne des valeurs
            std::cout << std::string(decalage, ' ');
            for (int i = 0; i <= n; ++i) {
                std::cout << std::left << std::setw(largeurCase) << _tree[n][i];
            }
            std::cout << "\n";

            // Ligne des branches vers le niveau suivant
            if (n < _depth) {
                std::string branches(decalage + (n + 1) * largeurCase, ' ');
                for (int i = 0; i <= n; ++i) {
                    int debutCase = decalage + i * largeurCase;
                    branches[debutCase + 1] = '/';    // vers le noeud du bas (i)
                    branches[debutCase + 5] = '\\';   // vers le noeud du haut (i+1)
                }
                std::cout << branches << "\n";
            }
        }
        std::cout << std::right << "\n";   // remet l'alignement par defaut
    }
};
