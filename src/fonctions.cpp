#include "fonctions.hpp"

// Ce code calcul la fonctionnelle e
// Nous calculons la valeur de chaque fonctionnelle puis nous faisons la somme 

double fonctionnelle(const Matrice &image, const Vecteur &x)
{   
    // Définition des valeurs de chaque fonctionnelle
    double e1 = 0, e2 = 0, e3 = 0;
    int n_ligne = image.n; // nombres de lignes de la matrice image
    int n_colonne = image.m; // nombres de colonne de la matrice image
    Matrice p = toMatrice(x(0, n_ligne * n_colonne - 1),n_ligne, n_colonne); // définition de la dérivée de la hauteur par rapport à x
    Matrice q = toMatrice(x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1),n_ligne, n_colonne); // définition de la dérivée de la hauteur par rapport à y

    for (int i = 1; i <= n_ligne; i++)
    {
        for (int j = 1; j <= n_colonne; j++)
        {
            e1 += pow(image(i, j) - 255 / sqrt(1 + pow(p(i, j), 2) + pow(q(i, j), 2)), 2);
            // si (i,j) est dans le domaine D1 
            if (i != n_ligne && j != n_colonne)
            {
                e2 += pow((p(i, j + 1) - p(i, j)) - q(i + 1, j) + q(i, j), 2);
                e3 += pow(p(i + 1, j) - p(i, j), 2) + pow(p(i, j + 1) - p(i, j), 2) + pow(q(i + 1, j) - q(i, j), 2) + pow(q(i, j + 1) - q(i, j), 2);
            }
        }
    }
    // on retourne la fonctionnelle globale avec chaque facteurs de pénalisation 
    return delta * delta * e1 + lambda_int * e2 + lambda_csmo * e3;
}

// Ce code calcul le gradient de la fonctionnelle e
// Nous calculons la valeur de chaque gradient de fonctionnelle puis nous faisons la somme comme 

Matrice grad_fonctionnelle(const Matrice &image, const Vecteur &x)
{
    int n_ligne = image.n;
    int n_colonne = image.m;

    Matrice p = toMatrice(x(0, n_ligne * n_colonne - 1),n_ligne, n_colonne); 
    Matrice q = toMatrice(x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1),n_ligne, n_colonne);

    Matrice e1(2 * n_ligne, n_colonne); 
    Matrice e2(2 * n_ligne, n_colonne);
    Matrice e3(2 * n_ligne, n_colonne);

    for (int i = 1; i <= n_ligne; i++)
    {
        for (int j = 1; j <= n_colonne; j++)
        {

            e1(i, j) = 2 * 255 * (image(i, j) * sqrt(1 + pow(p(i, j), 2) + pow(q(i, j), 2)) - 255) * (p(i, j) / pow(1 + pow(p(i, j), 2) + pow(q(i, j), 2), 2));
            // si (i,j) est dans le domaine D1 
            if (i != 1 && j != 1 && i != n_ligne && j != n_colonne)
            {
                e2(i, j) = 2 * p(i, j) - p(i, j - 1) - p(i, j + 1) - q(i, j) + q(i + 1, j) - q(i + 1, j - 1) + q(i, j - 1);
                e3(i, j) = 4 * p(i, j) - p(i - 1, j) - p(i + 1, j) - p(i, j - 1) - p(i, j + 1);
            }
        }
    }

    for (int i = n_ligne + 1; i <= 2 * n_ligne; i++)
    {
        for (int j = 1; j <= n_colonne; j++)
        {
            e1(i, j) = 2 * 255 * (image(i - n_ligne, j) * sqrt(1 + pow(p(i - n_ligne, j), 2) + pow(q(i - n_ligne, j), 2)) - 255) * (q(i - n_ligne, j) / pow(1 + pow(p(i - n_ligne, j), 2) + pow(q(i - n_ligne, j), 2), 2));
            // si (i,j) est dans le domaine D1 
            if (i != n_ligne + 1 && j != 1 && i != 2 * n_ligne && j != n_colonne)
            {
                e2(i, j) = 2 * q(i - n_ligne, j) - q(i - 1 - n_ligne, j) - q(i + 1 - n_ligne, j) - p(i - n_ligne, j) + p(i - n_ligne, j + 1) - p(i - 1 - n_ligne, j + 1) + p(i - 1 - n_ligne, j);
                e3(i, j) = 4 * q(i - n_ligne, j) - q(i - 1 - n_ligne, j) - q(i + 1 - n_ligne, j) - q(i - n_ligne, j - 1) - q(i - n_ligne, j + 1);
            }
        }
    }
    e1 *= delta * delta;
    e2 *= 2*lambda_int;
    e3 *= 2*lambda_csmo;


    return e1 + e2 + e3;
}

// Ce code calcule la fonctionnelle hauteur

double fonctionnelle_hauteur(const Matrice &x, const Vecteur &h)
{
    double result = 0;
    int n_ligne = x.n / 2;
    int n_colonne = x.m;
    Matrice hauteur = toMatrice(h,n_ligne, n_colonne);

    for (int i = 1; i < n_ligne; i++)
    {
        for (int j = 1; j < n_colonne; j++)
        {
            result += pow((hauteur(i + 1, j) - hauteur(i, j) - delta * x(i, j)), 2) + pow(hauteur(i, j + 1) - hauteur(i, j) - delta * x(i + n_ligne, j), 2);
        }
    }

    return result;
}

// Ce code calcule le gradient de la fonctionnelle hauteur
Matrice grad_fonctionnelle_hauteur(const Matrice &Image,const Vecteur &h)
{
    int nb_l = Image.n / 2;
    int nb_c = Image.m;
    Matrice hauteur = toMatrice(h,nb_l, nb_c);
    Matrice gradient(nb_l, nb_c, 0);

    for (int i = 1; i < nb_l + 1; i++)
    {
        for (int j = 1; j < nb_c + 1; j++)
        {
            // si (i,j) n'est pas au bord du domaine
            if (i != 1 && j != 1 && i != nb_l && j != nb_c)
            {
                gradient(i, j) = 4 * hauteur(i, j) - hauteur(i - 1, j) - delta * Image(i - 1, j) - hauteur(i + 1, j) + delta * Image(i, j) - hauteur(i, j - 1) - delta * Image(i + nb_l, j - 1) - hauteur(i, j + 1) + delta * Image(i + nb_l, j);
            }
        }
    }
    return 2 * gradient;
}

// Ce code calcule le pas de descente alpha tel que les conditions de Wolfe soient respectées (cas 1)

double Wolfe(const Matrice &Image, Vecteur &x, Vecteur &z, Vecteur &gradient)
{

    int i = 0;
    double alpha = 1;
    Vecteur x_new = x + alpha * z;
    double e_new = fonctionnelle(Image, x_new);
    double e = fonctionnelle(Image, x);
    double grad_e_pk = gradient | z;
    Vecteur grad_e_new = toVecteur(grad_fonctionnelle(Image, x_new));

    while(i<i_max_Wolfe){

        // Si les conditions de Wolfe sont respectées 
        if(e_new<=e+w1*alpha*grad_e_pk && abs(grad_e_new|z)<=w2*abs(grad_e_pk) ){
            return alpha;
        }
        i++;
        alpha /= 2;
        // mise à jour des fonctionnelles 
        x_new = x + alpha * z;
        e_new = fonctionnelle(Image, x_new);
        grad_e_new = toVecteur(grad_fonctionnelle(Image, x_new));
    }
    return alpha;
}


// Ce code calcule le pas de descente alpha tel que les conditions de Wolfe soient respectées (cas minimisation de la fonction hauteur)

double Wolfe_hauteur(const Matrice &Image, Vecteur &x, Vecteur &z, Vecteur &gradient)
{

    int i = 0;
    double alpha = 1;
    Vecteur x_new = x + alpha * z;
    double e_new = fonctionnelle_hauteur(Image, x_new);
    double e = fonctionnelle_hauteur(Image, x);
    double grad_e_pk = gradient | z;
    Vecteur grad_e_new = toVecteur(grad_fonctionnelle_hauteur(Image, x_new));
    while(i<i_max_Wolfe){
        if(e_new<=e+w1*alpha*grad_e_pk && abs(grad_e_new|z)<=w2*abs(grad_e_pk)){
            return alpha;
        }
        i++;
        alpha /= 2;
        x_new = x + alpha * z;
        e_new = fonctionnelle_hauteur(Image, x_new);
        grad_e_new = toVecteur(grad_fonctionnelle_hauteur(Image, x_new));
    }
    return alpha;
}