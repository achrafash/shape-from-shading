#ifndef __VECTEUR__
#define __VECTEUR__
#include <iostream>
#include <cmath>
#include "./matrice.hpp"
using namespace std;

template <typename T>
class Vecteur
{
public:
    int dim;
    T *val;
    //Constructeurs
    Vecteur() : dim(0), val(0){};
    Vecteur(int d, T x = T(0))
    {
        dim = d;
        val = new T[dim];
        for (int i = 0; i < dim; i++)
        {
            val[i] = x;
        }
    };
    Vecteur(const Vecteur &V)
    {
        dim = V.dim;
        val = new T[dim];
        for (int i = 0; i < dim; i++)
        {
            val[i] = V.val[i];
        }
    };

    //Destructeur
    ~Vecteur()
    {
        if (val != 0)
            delete[] val;
    };

    //Opérateurs internes
    Vecteur<T> &operator+=(const T);
    Vecteur<T> &operator-=(const T);
    Vecteur<T> &operator*=(const T);
    Vecteur<T> &operator/=(const T);
    Vecteur<T> operator+(const Vecteur<T> &A);
    Vecteur<T> operator-(const Vecteur<T> &A);
    Vecteur<T> operator*(const T);
    T operator*(const Vecteur<T> &);
    T &operator()(int) const;
    //Opérateur print
    template <typename type>
    friend ostream &operator<<(ostream &, const Vecteur<type> &);
    //Norme
    double norm();
};



#endif