#ifndef __VECTEUR__
#define __VECTEUR__
#include <iostream>
#include <cmath>
#include "matrice.hpp"
using namespace std;

// Définition de notre classe Vecteur avec un template

template <typename T>
class Vecteur{
  public:
    int dim; // Dimensions
    T *val; // tableau de valeur
    //Constructeurs
    Vecteur(); 
    Vecteur(int d, T x = T(0));
    Vecteur(const Vecteur &V);

    //Destructeur
    ~Vecteur();
    void clear();

    // initialisation 
    void init(int d, T x = T(0));

    //Opérateurs internes
    Vecteur<T> &operator=(const Vecteur<T> &V); // u=V;
    Vecteur<T> &operator*=(const T a); // u*=a;
    Vecteur<T> &operator/=(const T a); // u/=a;
    // Opérateurs externes 
    Vecteur<T> operator+(const Vecteur<T> &V); // opérateur +V
    Vecteur<T> operator-(const Vecteur<T> &V); // opérateur +V
    Vecteur<T> operator*(const T a); // opérateur *a
    Matrice toMatrice(const int i, const int j) const; // Transformation en matrice
    T operator*(const Vecteur<T> &);
    T operator|(const Vecteur<T> &V); // produit scalaire
    T &operator()(int) const; // accès lecture et écriture
    Vecteur<T> operator()(int, int) const; 
    //Opérateur print
    template <typename type>
    friend ostream &operator<<(ostream &, const Vecteur<type> &); // affichage
    //Norme
    double norm(); // calcul la norme d'un vecteur 
};


//Definition des methodes

//Constructeurs
template <typename T>
Vecteur<T>::Vecteur() : dim(0), val(nullptr){};

template <typename T>
Vecteur<T>::Vecteur(int d, T v){
    dim = d;
    val = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = v;
    }
};

template <typename T>
Vecteur<T>::Vecteur(const Vecteur<T> &V){
    dim = V.dim;
    val = nullptr;
    if(dim<=0) return;
    val = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = V.val[i];
    }
};

//Destructeur
template <typename T>
Vecteur<T>::~Vecteur(){
    if (val != nullptr){
        delete[] val;
        val = nullptr;
    }
};

template <typename T>
void Vecteur<T>::clear(){
    if (val != nullptr){
        // cout << "dimension : "<< dim << endl;
        delete[] val;
        // cout << "cleared" <<endl;
        val = nullptr;
    }
}

// initialisation 
template <typename T>
void Vecteur<T>::init(int d, T x ){
    dim = d;
    val = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = x;
    }
}

//Opérations internes
template <typename T>
Vecteur<T> &Vecteur<T>::operator=(const Vecteur<T> &V){
    dim = V.dim;
    clear();
    val = new T[dim];
    for (int i = 0; i < dim; i++){
        val[i] = V.val[i];
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator*=(const T a){
    for (int i = 0; i < dim; i++){
        val[i] *= a;
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator/=(const T a){
    if (a == 0){
        cout << "DIVISION BY ZERO : function operator/= ";
        exit(0);
    }
    for (int i = 0; i < dim; i++){
        val[i] /= a;
    }
    return *this;
};

template <typename T>
T &Vecteur<T>::operator()(int i) const{
    return val[i - 1];
};

template <typename T>
Vecteur<T> Vecteur<T>::operator()(int i, int j) const{
    if (i >= j){
        cout << "ERREUR EXTRACTION VECTEUR \n";
        exit(0);
    }
    int dim = j - i + 1;
    Vecteur temp(dim);
    for (int k = 0; k < dim; k++){
        temp.val[k] = val[i + k];
    }
    return temp;
}
template <typename T>
Vecteur<T> Vecteur<T>::operator+(const Vecteur<T> &V){
    if (V.dim != this->dim){
        cout << "ERREUR DIMENSION \n";
        exit(0);
    }
    Vecteur<T> e = *this;
    for (int i = 0; i < V.dim; i++){
        e.val[i] += V.val[i];
    }
    return e;
};
template <typename T>
Vecteur<T> Vecteur<T>::operator-(const Vecteur<T> &V){
    if (V.dim != this->dim){
        cout << "ERREUR DIMENSION \n";
        exit(0);
    }
    Vecteur<T> e = *this;
    for (int i = 0; i < V.dim; i++)
    {
        e.val[i] -= V.val[i];
    }
    return e;
};

template <typename T>
Vecteur<T> Vecteur<T>::operator*(const T a){
    Vecteur V = *this;
    for (int i = 0; i < dim; i++)
    {
        V.val[i] *= a;
    }
    return V;
};


template <typename T>
Matrice Vecteur<T>::toMatrice(const int i, const int j)const{
    if (i * j != dim){
        cout << "ERREUR DIMENSION : function ToMatrice \n";
        exit(0);
    }
    Matrice e(i, j);
    for (int k = 0; k < i; k++){
        for (int l = 0; l < j; l++){
            e.val[k][l] = val[l+k*j];
        }
    }
    return e;
}

//Produit scalaire
template <typename T>
T Vecteur<T>::operator|(const Vecteur<T> &V){
    T result = T(0);
    for (int i = 0; i < dim; i++){
        result += val[i] * V.val[i];
    }
    return result;
}

//Opérateur print
template <typename T>
ostream &operator<<(ostream &out, const Vecteur<T> &V){
    out << "( ";
    for (int i = 0; i < V.dim; i++){
        out << V.val[i] << " ";
    }
    out << ")\n";
    return out;
};

//Norme
template <typename T>
double Vecteur<T>::norm(){
    double result = (*this)|(*this);
    return sqrt(result);
};
template <typename T>
Vecteur<T> operator*(const T a,const Vecteur<T>& V){

    Vecteur<T> e = V;
    e*= a;
    return e;

}
template <typename T>

Vecteur<T> operator*(const Vecteur<T>& V,const T a){
    return a*V;
}

// moyenne pour initialiser la hauteur 
template <typename T>
double mean(Vecteur<T>& v)
{
    double m = v(1);
    for(int i=2;i<=v.dim;i++){
        m+=v(i);
    }
    return m/v.dim;
};

#endif
