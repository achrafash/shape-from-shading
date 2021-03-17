#ifndef __MATRICE__
#define __MATRICE__
#include <string>
#include <vector>
#include "vecteur2.hpp"

using namespace std;
class Vecteur;
class Matrice:public vector<Vecteur>{
  public:
	int n, m;	// Nombre de lignes, colonnes
	
	// Constructeurs
	Matrice();								 
	Matrice(int n_l, int n_c);				 
	Matrice(int n_l, int n_c, double valeur); 
	Matrice(const Matrice &M);				 	
	// Destructeur
	~Matrice();


	virtual Matrice ToIdentity();
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
	Matrice &operator/=(const double a);
	Matrice &operator*=(const double a);

	Matrice &operator+=(const Matrice &M);
	Matrice &operator-=(const Matrice &M);

	// Opérateurs d'affichage

	void print(); // Affichage
	friend ostream &operator<<(ostream &, const Matrice &M); // Affichage
};

Vecteur toVecteur(const Matrice &M);
Matrice operator*(const Matrice& M,const double a);
Matrice operator*(const double nb,const Matrice& M);
Matrice operator/(const Matrice& M,const double a);

Vecteur operator*(const Matrice &H,const Vecteur &V);

Matrice toMatrice(const Vecteur& v, const int i, const int j); // Transformation en matrice

struct Coord{
	int i;
	int j;
};

class Sparse:public Matrice{
	public:
	vector<vector<Coord>> Coord_non_nul;	
	Sparse(int n,int m);
	Sparse& operator=(const Sparse& S);
	void Toidentity();
	~Sparse();
};

Sparse operator*(const Sparse& S,const double a);
Sparse operator*(const double a,const Sparse& S);
Vecteur operator*(const Sparse& S,const Vecteur& V);
#endif