#include "matrice.hpp"
#include "vecteur.hpp"
#include "fonctions.hpp"
#include <vector>

using namespace std;

// Définition des précisions 

const double epsilon_1 = 100;
const double epsilon_2 = 10e-3;

// Définition du nombres d'itérations maximales du L-BFGS

const int i_max = 10000;

// Définition des fonctions 

Vecteur<double> BFGS(const Matrice& Image,Vecteur<double>& x);
// Vecteur<double> BFGS_hauteur(const Matrice& Image,Vecteur<double>& x);

double fonctionnelle_BFGS(const Matrice& image,const Vecteur<double>& x,const char* str);