#ifndef __MATRICE__
#define __MATRICE__
#include <string>

using namespace std;
class Vecteur;
class Matrice{
  public:
	int n, m;	// Nombre de lignes, colonnes
	double **val; // Tableau de valeurs

	// Constructeurs
	Matrice();								 
	Matrice(int n_l, int n_c);				 
	Matrice(int n_l, int n_c, double valeur); 
	Matrice(const Matrice &M);				 	
	// Destructeur
	~Matrice();


	Matrice ToIdentity();
	// Opérateurs

	Matrice &operator=(const Matrice &M); // copie
	double &operator()(int i, int j) const; // accès à un élement (lecture/écriture)

	Matrice operator+(const Matrice &M) const;
	Matrice operator-(const Matrice &M) const;
	Matrice operator*(const Matrice &M) const;
	//Vecteur<double> operator*(const Vecteur<double> &V) const; // produit Matrice, Vecteur

	// Opérations sur les matrices
	Matrice operator*(const double a);
	Matrice operator/(const double a) const;
	Matrice& operator/=(const double a);
	Matrice& operator*=(const double a);

	Matrice& operator+=(const Matrice &M);
	Matrice& operator-=(const Matrice &M);

	double norm(); // Norme 
	// Opérateurs d'affichage

	void print(); // Affichage
	friend ostream &operator<<(ostream &, const Matrice &M); // Affichage
};

Vecteur<double> toVecteur(const Matrice &M);
Matrice operator*(const Matrice& M,const double a);
Matrice operator*(const double nb,const Matrice& M);
Matrice operator/(const Matrice& M,const double a);

Vecteur<double> operator*(const Matrice &H,const Vecteur<double> &V);



// Concept C++, 

// Test avec des paramètres de visualisation 

// Insister sur la validation et les exemples

#endif