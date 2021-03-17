#include "matrice2.hpp"
#include "vecteur2.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//Définition de la classe des matrices

// Constructeurs
Matrice::Matrice()
{
	n = 0;
	m = 0;
};

Matrice::Matrice(int n_l, int n_c)
{
	n = n_l;
	m = n_c;
	resize(n);

	for (int i = 0; i < n; i++)
	{
		(*this)[i] = Vecteur(m,0);
	}
};

Matrice::Matrice(int n_l, int n_c, double valeur)
{
	n = n_l;
	m = n_c;
	resize(n);

	for (int i = 0; i < n; i++)
	{
		(*this)[i] = Vecteur(m,valeur);
	}
};

Matrice::Matrice(const Matrice &M)
{
	n = M.n;
	m = M.m;
	resize(n);

	for (int i = 0; i < n; i++)
	{
		(*this)[i] = Vecteur(M[i]);
	}
};


// Destructeur

Matrice::~Matrice()
{
	if ((*this).size()!=0){
		for (int i = 0; i < n; i++){
			(*this)[i].~Vecteur();
		}
		n = 0;
		m = 0;
		(*this).clear();
	}
};

// Opérateurs

Matrice &Matrice::operator=(const Matrice &M)
{
	if (this != &M) //assignation M = M impossible
	{
		if (M.n != n || M.m != m) // si tailles pas compatibles
		{
			for (int i = 0; i < n; i++)
			{
				(*this).clear();
			}
			n = M.n;
			m = M.m;
			resize(n);
		}
	}

	for (int i = 0; i < n; i++)
	{
		(*this)[i] = Vecteur(M[i]);
	}
	return *this;
};

double &Matrice::operator()(int i, int j) const
{
	if (i > n || j > m) // si out of range
	{
		cout << "Erreur: les indices sont trop grands. \n";
		exit(1);
	}
	return (*this)[i - 1](j);
};

Matrice Matrice::operator+(const Matrice &M) const
{
	Matrice tmp(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp[i][j] = (*this)[i][j] + M[i][j];

	return tmp;
};

Matrice Matrice::operator-(const Matrice &M) const
{
	Matrice tmp(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp[i][j] = (*this)[i][j] - M[i][j];

	return tmp;
};

Matrice Matrice::operator*(const Matrice &M) const
{
	Matrice tmp(n, M.m, 0);
	if (m == M.n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < M.m; j++)
			{
				for (int k = 0; k < m; k++)
					tmp[i][j] = (*this)[i][k] - M[k][j];

			}
	}
	else
	{
		cout << "ERROR : FUNCTION OPERATOR * BETWEEN TWO MATRICES\n";
		exit(1);
	}
	return tmp;
};
/*
Vecteur<double> Matrice::operator*(const Vecteur<double> &V) const
{
	if (m != V.dim)
	{
		cout << "Les dimensions ne correspondent pas. \n";
		exit(1);
	}
	Vecteur<double> temp(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			temp.val[i] += val[i][j] * V.val[j];
		}
	}
	return temp;
};
*/
Matrice Matrice::operator*(const double nb)
{
	Matrice tmp(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp[i][j] = (*this)[i][j] * nb;

	return tmp;
};

Matrice Matrice::operator/(const double nb) const
{
	Matrice tmp(n, m);
	if (nb)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp[i][j] /= nb;
	}
	else //exception division par 0
	{
		cout << "ERROR : DIVISION BY ZERO \n";
		exit(1);
	}
	return tmp;
};

Matrice &Matrice::operator*=(const double nb)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			(*this)[i][j] = (*this)[i][j] * nb;

	return *this;
};

Matrice &Matrice::operator/=(const double a)
{
	if (a != 0){
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				(*this)[i][j] /= a;
	}
	else{
		cout << "ERROR : DIVISION BY ZERO\n";
		exit(1);
	}
	return *this;
};

Matrice &Matrice::operator+=(const Matrice &M)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			(*this)[i][j] += M[i][j];

	return *this;
};

Matrice &Matrice::operator-=(const Matrice &M)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			(*this)[i][j] -= M[i][j];

	return *this;
};

// Opérateurs d'affichage

void Matrice::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << (*this)[i][j] << " ";
		}
		cout << "\n";
	}
};

ostream &operator<<(ostream &out, const Matrice &M)
{
	if (M.size()==0)
	{
		cout << "ERROR : CANNOT PRINT A EMPTY MATRICE \n";
		exit(1);
	}
	for (int i = 0; i < M.n; i++)
	{
		for (int j = 0; j < M.m; j++)
		{
			cout << M[i][j] << " ";
		}
		cout << "\n";
	}
	return out;
};

// Opérateurs externes

Vecteur toVecteur(const Matrice &M)
{
	int dim = M.n * M.m;
	Vecteur V(dim);
	for (int i = 0; i < M.n; i++)
	{
		for (int j = 0; j < M.m; j++)
		{
			V.val[i * M.m + j] = M[i][j];
		}
	}
	return V;
};


Matrice operator*(const Matrice &M, const double a)
{
	Matrice e = M;
	e *= a;
	return e;
}
Matrice operator*(const double a, const Matrice &M)
{
	return M * a;
}

Matrice Matrice::ToIdentity(){

	if(n!=m){
		cout << "ERROR :: MATRICE WITH DIFFERENT ::CANNOT CREATE THE IDENTITY MATRIX" << endl;
		exit(0);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i==j){
				(*this)[i][j] = 1;
			} 
			else{
				(*this)[i][j] = 0;
			}
		}
	}
	return *this;

}

Vecteur operator*(const Matrice &H,const Vecteur &V){
	int n = H.n;
	if (n != V.dim)
	{
		cout << "ERROR :: CANNOT PROCEDE THIS PRODUCE OF A MATRIX AND A VECTOR :: ERROR ON DIMENSION \n";
		exit(1);
	}
	Vecteur temp(n);
	for (int i = 0; i < n; i++){
		for(int j=0;j<n;j++){
			temp.val[i] += H[i][j] * V.val[j];
		}
	}
	return temp;
	
}

Matrice toMatrice(const Vecteur& v,const int i, const int j){
    if (i * j != v.dim){
        cout << "ERREUR DIMENSION : function ToMatrice \n";
        exit(0);
    }
    Matrice e(i, j);
    for (int k = 0; k < i; k++){
        for (int l = 0; l < j; l++){
            e[k][l] = v.val[l+k*j];
        }
    }
    return e;
}

// SPARSE


// 

Sparse::Sparse(int n_l,int n_c):Matrice(n_l,n_c){

	n = n_l;
	m = n_c;

	(*this).clear();
	(*this).resize(n);
	for(int i=0;i<n;i++){
		(*this)[i] = Vecteur();
	}
	Coord_non_nul.resize(n);
}

Sparse& Sparse::operator=(const Sparse& S){

	n = S.n;
	m = S.m;

	(*this).clear();
	(*this).resize(n);
	for(int i=0;i<n;i++){
		(*this)[i] = S[i];
	}
	Coord_non_nul.resize(n);
	for(int i=0;i<n;i++){
		Coord_non_nul[i].resize(S.Coord_non_nul[i].size());
		for(int j=0;j<Coord_non_nul[i].size();j++){
			Coord_non_nul[i][j] = S.Coord_non_nul[i][j];
		}
	}
}	

Sparse operator*(const Sparse& S,const double a ){
	Sparse S2 = S;
	for(int i=0;i<S.n;i++){
		for(int j=0;j<S[i].dim;j++){
			S2[i].val[j] = a *S[i].val[j];
		}
	}
	return S2;

}

Sparse operator*(const double a,const Sparse& S){

	return S*a;

}

Vecteur operator*(const Sparse& S,const Vecteur& V){

	Vecteur e(S.n,0);
	for(int i=0;i<S.n;i++){
		for(int j=0;j<S[i].dim;j++){
			e.val[i]+=S[i][j]*V[S.Coord_non_nul[i][j].j];
		}
	}
	return e;

}

void Sparse::Toidentity(){
	Vecteur diagonale(1,1);
	Coord indice = {0,0};
	for(int i=0;i<n;i++){
		//cout << "oui" << endl;
		(*this)[i] = Vecteur (1,1);
		indice.i = i;
		indice.j = i;
		Coord_non_nul[i].push_back(indice);

	}
	//cout << "première ligne" << (*this)[0] << endl;
}

Sparse::~Sparse(){
	//cout << (*this)[0] << endl;
	//cout << (*this)[1] << endl;
	//cout << (*this)[2] << endl;

	//cout << "clear" << endl;
	Coord_non_nul.clear();
	//cout << "clear" << endl;
	if ((*this).size()!=0){
		for (int i = 0; i < n; i++){
			//cout << "clear" << endl;
			//cout << "dim" << (*this)[i].dim << endl;
			(*this)[i].~Vecteur();
		}
		n = 0;
		m = 0;
		(*this).clear();
	}
}