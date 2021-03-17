#ifndef __LBFGS__
#define __LBFGS__

#include "matrice.hpp"
#include "vecteur.hpp"
#include "fonctions.hpp"
#include <vector>
#include <cmath>

using namespace std;

// Définition des précisions 

const double epsilon_1 = 50;
const double epsilon_2 = 10e-4;

// Définition du nombres d'itérations maximales du L-BFGS

const int i_max = 10000;

// Définition des fonctions 

Vecteur BFGS(const Matrice& Image,Vecteur& x);
Vecteur BFGS_hauteur(const Matrice& Image,Vecteur& x);

#endif