#include "matrice2.hpp"
#include "vecteur2.hpp"
/*
#include "matrice.hpp"
#include "vecteur.hpp"
*/
#include "fonctions.hpp"
#include <vector>

using namespace std;

// Définition des précisions 

const double epsilon_1 = 200;
const double epsilon_2 = 10e-3;

// Définition du nombres d'itérations maximales du L-BFGS

const int i_max = 10000;

// Définition des fonctions 

Vecteur BFGS(const Matrice& Image,Vecteur& x);
Vecteur BFGS_hauteur(const Matrice& Image,Vecteur& x);