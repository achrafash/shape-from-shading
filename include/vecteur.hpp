#ifndef vecteur_h
#define vecteur_h

#include <iostream>
using namespace std;

//utilitaires
void stop(const char *msg);                     //message d'arr�t
void test_dim(int d1, int d2, const char *org); //test dimension

//classe vecteur de r�els double pr�cision
template <typename T>
class vecteur
{
private:
    int dim_; //dimension du vecteur
    T *val_;  //tableaux de valeurs

public:
    vecteur(int d = 0, const T &v0 = 0); //dim et val constante
    vecteur(const vecteur<T> &v);        //constructeur par copie
    ~vecteur();

    //tools
    void init(int d);                //allocation
    void clear();                    //d�sallocation
    int dim() const { return dim_; } //acc�s dimension

    //op�rateur d'assignation
    vecteur<T> &operator=(const vecteur<T> &v); //assignation d'un vecteur
    vecteur<T> &operator=(const T &x);          //assignation d'une valeur

    //op�rateurs d'acc�s (pour les utilisateurs)
    T &operator()(int i) const { return val_[i - 1]; } //valeur    1->dim
    T &&operator()(int i) { return val_[i - 1]; }      //r�f�rence 1->dim

    //op�rateurs alg�briques
    vecteur<T> &operator+=(const vecteur<T> &v); // u += v
    vecteur<T> &operator-=(const vecteur<T> &v); // u -= v
    vecteur<T> &operator+=(const T &x);          // u += x
    vecteur<T> &operator-=(const T &x);          // u -= x
    vecteur<T> &operator*=(const T &x);          // u *= x
    vecteur<T> &operator/=(const T &x);          // u /= x

}; //fin de d�finition de la classe

//op�rateurs externes
template <typename T>
vecteur<T> operator+(const vecteur<T> &u); //+ unaire ne fait rien !
template <typename T>
vecteur<T> operator-(const vecteur<T> &u); //- unaire : chgt de signe

template <typename T, typename S>
vecteur<T> operator+(const vecteur<T> &u, const vecteur<S> &v); // u + v
template <typename T, typename S>
vecteur<T> operator-(const vecteur<T> &u, const vecteur<S> &v); // u - v
template <typename T, typename S>
vecteur<T> operator+(const vecteur<T> &u, const S &x); // u + x
template <typename T, typename S>
vecteur<T> operator+(const T &x, const vecteur<S> &u); // x + u

// vecteur operator-(const vecteur &u, double x);         // u - x
// vecteur operator-(double x, const vecteur &u);         // x - u
// vecteur operator*(const vecteur &u, double x);         // u * x
// vecteur operator/(const vecteur &u, double x);         // u / x
// vecteur operator+(double x, const vecteur &u);         // x + u
// vecteur operator-(double x, const vecteur &u);         // x - u
// vecteur operator*(double x, const vecteur &u);         // x * u
// double operator|(const vecteur &u, const vecteur &v);  // u | v
// double norme(const vecteur &u);                        // sqrt(u|u)

// //op�rateurs de comparaison
// bool operator==(const vecteur &u, const vecteur &v); // u == v
// bool operator!=(const vecteur &u, const vecteur &v); // u != v

//op�rateurs de lecture et d'�criture
template <typename T>
ostream &operator<<(ostream &os, const vecteur<T> &u); // os << u

#include "vecteur.cpp"
#endif