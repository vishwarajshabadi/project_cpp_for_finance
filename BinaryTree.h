#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

// Arbre binaire recombinant utilisé par la méthode CRR.
// Le niveau n (0 <= n <= N) contient n+1 noeuds, indexés par i (0 <= i <= n).
// Classe template : toute la définition reste dans le .h.
template <typename T>
class BinaryTree {
private:
    int _depth;                          // N : nombre de pas de temps
    std::vector<std::vector<T>> _tree;   // _tree[n][i] = valeur au pas n, noeud i

    // Vérifie que les indices (n, i) existent dans l'arbre
    void checkIndices(int n, int i) const {
        if (n < 0 || n > _depth || i < 0 || i > n)
            throw std::out_of_range("BinaryTree : indices (n, i) hors de l'arbre");
    }

public:
    BinaryTree() : _depth(0) { setDepth(0); }
    explicit BinaryTree(int depth) : _depth(0) { setDepth(depth); }

    // Fixe N et redimensionne l'arbre : N+1 niveaux, le niveau n ayant n+1 noeuds.
    // resize() alloue les nouveaux vecteurs et libère ceux qui ne servent plus.
    void setDepth(int depth) {
        if (depth < 0)
            throw std::invalid_argument("BinaryTree : la profondeur doit etre >= 0");
        _depth = depth;
        _tree.resize(_depth + 1);
        for (int n = 0; n <= _depth; ++n)
            _tree[n].resize(n + 1);
    }

    int getDepth() const { return _depth; }

    void setNode(int n, int i, T value) {
        checkIndices(n, i);
        _tree[n][i] = value;
    }

    T getNode(int n, int i) const {
        checkIndices(n, i);
        return _tree[n][i];
    }

    // Affiche les valeurs de deux façons :
    // 1) ligne par ligne (un niveau n par ligne)
    // 2) sous forme d'arbre, avec les branches / et \ .
    void display() const {
        // 1) Affichage ligne par ligne
        for (int n = 0; n <= _depth; ++n) {
            for (int i = 0; i <= n; ++i)
                std::cout << _tree[n][i] << (i < n ? "\t" : "");
            std::cout << "\n";
        }
        std::cout << "\n";

        // 2) Affichage en arbre
        // Largeur d'une "case" = longueur de la plus longue valeur affichée + 1
        int w = 4;
        for (const auto& niveau : _tree)
            for (const T& v : niveau)
                w = std::max(w, (int)toString(v).size() + 1);
        if (w % 2 == 1) ++w;   // largeur paire : les branches tombent pile entre deux noeuds

        const int largeurTotale = (2 * _depth + 1) * w + w;
        for (int n = 0; n <= _depth; ++n) {
            // Ligne des valeurs du niveau n
            std::string ligne(largeurTotale, ' ');
            for (int i = 0; i <= n; ++i) {
                std::string s = toString(_tree[n][i]);
                int centre = (_depth - n + 2 * i) * w + w / 2;
                int debut = std::max(0, centre - (int)s.size() / 2);
                ligne.replace(debut, s.size(), s);
            }
            std::cout << rtrim(ligne) << "\n";

            // Ligne des branches vers le niveau n+1
            if (n < _depth) {
                std::string branches(largeurTotale, ' ');
                for (int i = 0; i <= n; ++i) {
                    int centre = (_depth - n + 2 * i) * w + w / 2;
                    branches[centre - w / 2] = '/';
                    branches[centre + w / 2] = '\\';
                }
                std::cout << rtrim(branches) << "\n";
            }
        }
        std::cout << "\n";
    }

private:
    static std::string toString(const T& v) {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    }
    static std::string rtrim(std::string s) {
        s.erase(s.find_last_not_of(' ') + 1);
        return s;
    }
};
