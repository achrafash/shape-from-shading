#include <cstdlib>
#include <cmath>
#include "vecteur2.hpp"

//utilitaire de messages d'erreur
void stop(const char * msg)
{
  cout<<"ERREUR classe vecteur, " << msg;
  exit(-1);
}

void test_dim(int d1, int d2, const char * org)
{
  if(d1==d2)  return;
  cout<<org<<" ("<<d1<<","<<d2<<") dimensions incompatibles";
  exit(-1);
}


//Definition des methodes

//Constructeurs

Vecteur::Vecteur() : dim(0), val(nullptr){};


Vecteur::Vecteur(int d, double v){
    dim = d;
    val = new double[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = v;
    }
};


Vecteur::Vecteur(const Vecteur &V){
    dim = V.dim;
    val = nullptr;
    if(dim<=0) return;
    val = new double[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = V.val[i];
    }
};

//Destructeur

Vecteur::~Vecteur(){
    if (val != nullptr){
        delete[] val;
        val = nullptr;
    }
};


void Vecteur::clear(){
    if (val != nullptr){
        // cout << "dimension : "<< dim << endl;
        delete[] val;
        // cout << "cleared" <<endl;
        val = nullptr;
    }
}

// initialisation 

void Vecteur::init(int d, double x ){
    dim = d;
    val = new double[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = x;
    }
}

//Opérations internes

Vecteur &Vecteur::operator=(const Vecteur &V){
    dim = V.dim;
    clear();
    val = new double[dim];
    for (int i = 0; i < dim; i++){
        val[i] = V.val[i];
    }
    return *this;
};


Vecteur &Vecteur::operator*=(const double a){
    for (int i = 0; i < dim; i++){
        val[i] *= a;
    }
    return *this;
};


Vecteur &Vecteur::operator/=(const double a){
    if (a == 0){
        cout << "DIVISION BY ZERO : function operator/= ";
        exit(0);
    }
    for (int i = 0; i < dim; i++){
        val[i] /= a;
    }
    return *this;
};


double &Vecteur::operator()(int i) const{
    return val[i - 1];
};


Vecteur Vecteur::operator()(int i, int j) const{
    if (i >= j){
        cout << "ERREUR EXTRACTION VECTEUR \n";
        exit(0);
    }
    int dim = j - i + 1;
    Vecteur temp(dim);
    for (int k = 0; k < dim; k++){
        temp.val[k] = val[i + k];
    }
    return temp;
}

double& Vecteur::operator[](int i) const{

    return val[i];

}

Vecteur Vecteur::operator+(const Vecteur &V){
    if (V.dim != this->dim){
        cout << "ERREUR DIMENSION \n";
        exit(0);
    }
    Vecteur e = *this;
    for (int i = 0; i < V.dim; i++){
        e.val[i] += V.val[i];
    }
    return e;
};

Vecteur Vecteur::operator-(const Vecteur &V){
    if (V.dim != this->dim){
        cout << "ERREUR DIMENSION \n";
        exit(0);
    }
    Vecteur e = *this;
    for (int i = 0; i < V.dim; i++)
    {
        e.val[i] -= V.val[i];
    }
    return e;
};


Vecteur Vecteur::operator*(const double a){
    Vecteur V = *this;
    for (int i = 0; i < dim; i++)
    {
        V.val[i] *= a;
    }
    return V;
};


//Produit scalaire

double Vecteur::operator|(const Vecteur &V){
    double result = 0;
    for (int i = 0; i < dim; i++){
        result += val[i] * V.val[i];
    }
    return result;
}

//Opérateur print

ostream &operator<<(ostream &out, const Vecteur &V){
    out << "( ";
    for (int i = 0; i < V.dim; i++){
        out << V.val[i] << " ";
    }
    out << ")\n";
    return out;
};

//Norme

double Vecteur::norm(){
    double result = (*this)|(*this);
    return sqrt(result);
};

Vecteur operator*(const double a,const Vecteur& V){

    Vecteur e = V;
    e*= a;
    return e;

}


Vecteur operator*(const Vecteur& V,const double a){
    return a*V;
}

// moyenne pour initialiser la hauteur 

double mean(Vecteur& v)
{
    double m = v(1);
    for(int i=2;i<=v.dim;i++){
        m+=v(i);
    }
    return m/v.dim;
};