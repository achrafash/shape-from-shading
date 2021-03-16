#ifndef __VECTEUR__
#define __VECTEUR__
#include <iostream>
#include <cmath>
#include "matrice.hpp"
using namespace std;

// Définition de notre classe Vecteur avec un template

class Vecteur{
  public:
    int dim; // Dimensions
    double *val; // tableau de valeur
    //Constructeurs
    Vecteur(); 
    Vecteur(int d, double x = 0);
    Vecteur(const Vecteur &V);

    //Destructeur
    ~Vecteur();
    void clear();

    // initialisation 
    void init(int d, double x = 0);

    //Opérateurs internes
    Vecteur &operator=(const Vecteur &V); // u=V;
    Vecteur &operator*=(const double a); // u*=a;
    Vecteur &operator/=(const double a); // u/=a;
    // Opérateurs externes 
    Vecteur operator+(const Vecteur &V); // opérateur +V
    Vecteur operator-(const Vecteur &V); // opérateur +V
    Vecteur operator*(const double a); // opérateur *a
    Matrice toMatrice(const int i, const int j) const; // Transformation en matrice
    double operator*(const Vecteur &);
    double operator|(const Vecteur &V); // produit scalaire
    double &operator()(int) const; // accès lecture et écriture
    Vecteur operator()(int, int) const; 
    //Opérateur print
    friend ostream &operator<<(ostream &, const Vecteur &); // affichage
    //Norme
    double norm(); // calcul la norme d'un vecteur 
};




#endif
