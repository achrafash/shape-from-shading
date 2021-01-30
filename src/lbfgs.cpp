#include "lbfgs.hpp"
#include <cmath>


// Ce code calcul la fonctionnelle e 
// Nous allons calculer la valeur de chaque fonctionnelle puis on fera la somme

double fonctionnelle(const Matrice& image,const Matrice& p, const Matrice& q){

    double e1 = 0,e2 = 0, e3 = 0;
    int n_ligne = image.n;
    int n_colonne = image.m;

    for(int i=1;i<=n_ligne;i++){
        for(int j=1;j<=n_colonne;j++){
            e1 += pow(image(i,j)-255/sqrt(1+pow(p(i,j),2)+pow(q(i,j),2)),2);
            // si (i,j) est dans le domaine D1
            if(i!=n_colonne && j!=n_ligne){
                e2+=pow((p(i,j+1)-p(i,j))-(q(i+1,j)-q(i,j)),2);
                e3+=pow(p(i+1,j)-p(i,j),2)+pow(p(i,j+1)-p(i,j),2)+pow(q(i+1,j)-q(i,j),2)+pow(q(i,j+1)-q(i,j),2);
            }
        }
    }

    return delta*delta*e1+lambda_int*e2+lambda_csmo*e3;

}



// Ce code calcul le gradient de la fonctionnelle e 
// Nous allons calculer les gradients de chaque fonctionnelle puis on fera la somme



// A REVOIR



// Ce code calcul le gradient de la fonctionnelle discrétisée pour retrouver la hauteur
// Nous allons calculer les gradients de chaque fonctionnelle puis on fera la somme


// Ce code calcul la fonctionnelle hauteur

double fonctionnelle_hauteur(const Matrice& h, const Matrice& p, const Matrice& q){

    double result = 0;
    int n_ligne = p.n;
    int n_colonne = p.m;

    for(int i=1;i<n_ligne;i++){
        for(int j=1;j<n_colonne;j++){
               result += pow((h(i+1,j)-h(i,j)-delta*p(i,j)),2)+pow(h(i,j+1)-h(i,j)-delta*q(i,j),2);
        }
    }

    return result;


}
