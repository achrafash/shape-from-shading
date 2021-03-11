#include "matrice.hpp"
#include "vecteur.hpp"

// Définition des facteurs de pénalisation 

const double delta = 1;
const double lambda_int = 1 ;
const double lambda_csmo = 1;

// Définition des constantes de Wolfe (VOIR SYLLABUS OPT202 pour le choix des constantes )

const double w1 = 1.0e-4;
const double w2 = 0.99;

// Définition du nombre d'itérations maximales pour Wolfe

const int i_max_Wolfe = 20;

// Définition des fonctions permettant de faire fonctionner l'algorithme BFGS

double Wolfe(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient);
double Wolfe_hauteur(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient);
Matrice grad_fonctionnelle(const Matrice& image,const Vecteur<double>& x);
double fonctionnelle(const Matrice& image,const Vecteur<double>& x);
Matrice grad_fonctionnelle_hauteur(const Matrice& image,const Vecteur<double> &x);
double fonctionnelle_hauteur(const Matrice &x, const Vecteur<double> &h);

