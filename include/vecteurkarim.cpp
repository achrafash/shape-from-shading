#include <cstdlib>
#include <cmath>
#include "./vecteur.hpp"

template <typename T>
Vecteur<T> &Vecteur<T>::operator+=(const T a)
{
    for (int i = 0; i < dim; i++)
    {
        val[i] += a;
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator-=(const T a)
{
    for (int i = 0; i < dim; i++)
    {
        val[i] -= a;
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator*=(const T a)
{
    for (int i = 0; i < dim; i++)
    {
        val[i] *= a;
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator/=(const T a)
{
    if (a == 0)
    {
        exit(1);
    }
    else
    {
        for (int i = 0; i < dim; i++)
        {
            val[i] /= a;
        }
        return *this;
    }
};


template <typename T>
Vecteur<T> Vecteur<T>::operator+(const Vecteur<T> &A)
{
    if (A.dim != this->dim)
    {
        cout << "Les vecteurs n'ont pas la même dimension. \n";
        exit(1);
    }
    Vecteur<T> C = *this;
    for (int i = 0; i < A.dim; i++)
    {
        C.val[i] += A.val[i];
    }
    return C;
};

template <typename T>
Vecteur<T> Vecteur<T>::operator-(const Vecteur<T> &A)
{
    if (A.dim != this->dim)
    {
        cout << "Les vecteurs n'ont pas la même dimension. \n";
        exit(1);
    }
    Vecteur<T> C = *this;
    for (int i = 0; i < A.dim; i++)
    {
        C.val[i] -= A.val[i];
    }
    return C;
};

template <typename T>
T &Vecteur<T>::operator()(int i) const
{
    return val[i - 1];
};

template <typename T>
Vecteur<T> Vecteur<T>::operator*(const T a)
{
    Vecteur V = *this;
    for (int i = 0; i < dim; i++)
    {
        V.val[i] *= a;
    }
    return V;
};

//Produit scalaire
template <typename T>
T Vecteur<T>::operator*(const Vecteur<T> &V)
{
    T ps = T(0);
    for (int i = 0; i < dim; i++)
    {
        ps += val[i] * V.val[i];
    }
    return ps;
}

//Opérateur print
template <typename T>
ostream &operator<<(ostream &out, const Vecteur<T> &V)
{
    out << "( ";
    for (int i = 0; i < V.dim; i++)
    {
        out << V.val[i] << ";";
    }
    out << ")\n";
    return out;
};

//Norme
template <typename T>
double Vecteur<T>::norm()
{
    double n = sqrt(((*this)*(*this)));
    return n;
};
