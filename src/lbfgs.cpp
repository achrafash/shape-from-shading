#include "include/lbfgs.hpp"
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

Matrice grad_fonctionnelle(const Matrice& image, const Matrice& p, const Matrice& q){
    
    int n_ligne = image.n;
    int n_colonne = image.m;
    // Matrice result(2*n_ligne,n_colonne);
    Matrice e1(2*n_ligne,n_colonne);
    Matrice e2(2*n_ligne,n_colonne);
    Matrice e3(2*n_ligne,n_colonne);

    for(int i=1;i<=n_ligne;i++){
        for(int j=1;j<=n_colonne;j++){

            e1(i,j) = 2 * 255 * (image(i,j)*sqrt(1+pow(p(i,j),2)+pow(q(i,j),2))-255)*(p(i,j)/pow(1+pow(p(i,j),2)+pow(q(i,j),2),2));
            e2(i,j) = 0; // calcul à faire
            e3(i,j) = 0;
        }
    }

    for(int i=n_ligne+1;i<=2*n_ligne;i++){
        for(int j=n_ligne+1;j<=2*n_ligne;j++){

            e1(i,j) = 2 * 255 * (image(i,j)*sqrt(1+pow(p(i,j),2)+pow(q(i,j),2))-255)*(q(i,j)/pow(1+pow(p(i,j),2)+pow(q(i,j),2),2));
            e2(i,j) = 0; // calcul à faire
            e3(i,j) = 0;
        }
    }
    e1*=delta*delta;
    e2*=lambda_int;
    e3*=lambda_csmo;

    // coder l'opérateur + pour return delta*delta*e1+lambda_int*e2+...

    return e1+e2+e3;

}


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

// Ce code calcul le gradient de la fonctionnelle discrétisée pour retrouver la hauteur
// Nous allons calculer les gradients de chaque fonctionnelle puis on fera la somme


 
// Méthode BFGS

Matrice BFGS(const Matrice& Image){

    int n = Image.n;
    int m = Image.m;
    Matrice p(n,m);
    Matrice q(n,m);

    Vecteur<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    Vecteur<Vecteur<double>> y(m); 

    int k = 0;
    bool finish = false;
    while(k<i_max && finish == false){

        // Calcul du gradient de la fonctionnelle
        
        // Calcul de gamma et de Ho_k

        // Calcul de la direction de descente H_k * grad(e) 

        


    }



}

