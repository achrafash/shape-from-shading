#include "matrice.hpp"
#include "vecteur.hpp"
#include <vector>

const double delta = 1;
const double lambda_int = 1 ;
const double lambda_csmo = 1;

const double w1 = 1.0e-6;
const double w2 = 1.0e-6;
const double epsilon = 10e-6;
const int i_max = 3;

Vecteur<double> BFGS(const Matrice& Image,Vecteur<double>& x);
Vecteur<double> BFGS_hauteur(const Matrice& Image,Vecteur<double>& x);
double Wolfe(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient);
double Wolfe_hauteur(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient);
Matrice grad_fonctionnelle(const Matrice& image,const Vecteur<double>& x);
double fonctionnelle_hauteur(const Matrice& h, const Matrice& p, const Matrice& q);
double fonctionnelle(const Matrice& image,const Vecteur<double>& x);
Vecteur<double> grad_fonctionnelle_hauteur(const Matrice& image,const Vecteur<double>& x);
