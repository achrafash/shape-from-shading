#include "matrice.hpp"
#include "vecteur.hpp"
#include "fonctions.hpp"
#include <vector>
#include <string>

using namespace std;

// Définition des précisions 

const double epsilon_1 = 100;
const double epsilon_2 = 10e-3;

// Définition du nombres d'itérations maximales du L-BFGS

const int i_max = 10000;

// Définition des fonctions 

Vecteur<double> BFGS(const Matrice& Image,Vecteur<double>& x,string option);
// Vecteur<double> BFGS_hauteur(const Matrice& Image,Vecteur<double>& x);

double fonctionnelle_BFGS(const Matrice& image,const Vecteur<double>& x,string option);
Matrice grad_fonctionnelle_BFGS(const Matrice& image,const Vecteur<double> &x,string option);
double Wolfe_BFGS(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient,string option);