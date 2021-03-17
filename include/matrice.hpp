#ifndef __MATRICE__
#define __MATRICE__
#include <string>
#include <vector>
#include "vecteur.hpp"

using namespace std;
class Vecteur; // On appelle la classe  Vecteur car on l'utilise plus tard

// _______________________________________________________________________________CLASS MATRICE HÉRITANT DE vector<Vecteur>_____________________________________________________________________________

class Matrice:public vector<Vecteur>{ 
  public:
	int n, m;	// Nombre de lignes, colonnes
	
	// Constructeurs
	Matrice();								 
	Matrice(int n_l, int n_c);				 
	Matrice(int n_l, int n_c, double valeur); 
	Matrice(const Matrice &M);				 	
	// Destructeur
	virtual ~Matrice(); //Destructeur virtuel

	virtual void Toidentity(); // Fonction permettant de modifier la matrice en la matrice identité
	// Opérateurs

	virtual Matrice &operator=(const Matrice &M); // copie
	double &operator()(int i, int j) const; // accès à un élement (lecture/écriture)

	Matrice operator+(const Matrice &M) const; // opération +
	Matrice operator-(const Matrice &M) const; // opération -
	Matrice operator*(const Matrice &M) const; // opération *

	// Opérations sur les matrices
	virtual Matrice operator*(const double a); // opération *
	virtual Matrice operator/(const double a); // opération /
	virtual Matrice &operator/=(const double a); // opération /=
	virtual Matrice &operator*=(const double a); // opération *=

	virtual Matrice &operator+=(const Matrice &M); // opération +=
	virtual Matrice &operator-=(const Matrice &M); // opération -=

	friend ostream &operator<<(ostream &, const Matrice &M); // Affichage
};
// Opérateurs externes 
Vecteur toVecteur(const Matrice &M); // Passage de Matrice à vecteur
Matrice operator*(const Matrice& M,const double a); // operateur externes de multiplication entre une matrice et un double
Matrice operator*(const double a,const Matrice& M); // operateur externes de multiplication entre un double et une matrice
Matrice operator/(const Matrice& M,const double a); // operateur externes de division entre une matrice et un double
Vecteur operator*(const Matrice &H,const Vecteur &V); // operateur externes de multiplication entre une matrice et un vecteur

Matrice toMatrice(const Vecteur& v, const int i, const int j); // Transformation d'une vecteur en matrice

//  ________________________________STRUCTURE REPRÉSENTANT LES INDICES DE LA MATRICE DONT LES COEFFICIENTS SERONT NON NULS______________________________________________________

struct Coord{
	int i;
	int j;
};

// _________________________________________________________CLASS SPARSE : MATRICE CREUSE HÉRITANT DE MATRICE _________________________________________________________________

class Sparse:public Matrice{

	public:
	vector<vector<Coord>> Coord_non_nul;	// Vecteur contenant les coordonnées des indices dont les coefficients sont non nuls 
	Sparse(int n,int m); // Constructeur 
	Sparse& operator=(const Sparse& S); // Opérateur = 
	void Toidentity(); // Rendre la matrice 
	~Sparse(); // Destructeur de Sparse 
	void add(int i,int j,double value); // Ajout d'un coefficient de valeur value au coordonnées i et j dans la matrice 
};

Sparse operator*(const Sparse& S,const double a); // Opération de multiplication entre une matrice et un double
Sparse operator*(const double a,const Sparse& S);
Vecteur operator*(const Sparse& S,const Vecteur& V); // Opération de multiplication entre une matrice et un vecteur


#endif