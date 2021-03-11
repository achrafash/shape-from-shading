#include "lbfgs.hpp"
#include <cmath>

// Méthode BFGS

Vecteur<double> BFGS(const Matrice &Image, Vecteur<double> &x)
{
    Matrice Identity(x.dim,x.dim, 0);
    Identity.ToIdentity();
    cout << "oui" << endl;
    Vecteur<double> x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 5;
    vector<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    Vecteur<double> initial(x.dim, 1); // vecteur de vecteur de s allant de k-1 à k-m
    vector<Vecteur<double>> y(m); 
    for (int i = 0; i < m; i++)
    {
        s[i].init(x.dim, 0.01); 
        y[i].init(x.dim, 0.01);
    }
    Vecteur<double> alpha_k(m, 0);
    Vecteur<double> beta_k(m, 0);
    double gamma_k = 1; 
    double beta_i = 0;
    double alpha = 0;
    int k = 0; // Itérateur
    int indice = 0; 
    while (k < i_max)
    {
        // VOIR WIKIPEDIA POUR LE MODÈLE
        // Calcul du gradient de la fonctionnelle
        Vecteur<double> g_k = toVecteur(grad_fonctionnelle(Image, x));
        cout << "Itérations : " << k << endl;
        cout << "oui, norme du gradient : " << g_k.norm() << endl;
        // Test de la condition 
        if (g_k.norm() < epsilon_1)
        {
            return x;
        }
        Vecteur<double> q = g_k;
        // cout << "oui" << endl;
        double rho_i = 0;
        if(k>0){
            for (int i = k - 1; i >= k - m; i--)
            {
                if (i % m < 0)
                {
                    indice = i % m + m;
                }
                else
                {
                    indice = i % m;
                }
                rho_i = 1 / (y[indice] | s[indice]);
                alpha_k(indice + 1) = rho_i * s[indice] | q;
                q = q - alpha_k(indice + 1) * y[indice];
            }
        }
        if (k > 0)
        {
            // mise à jour de Gamma
            gamma_k = (s[(k - 1) % m] | y[(k - 1) % m]) / (y[(k - 1) % m] | y[(k - 1) % m]);
        }
        Matrice H_k0 = gamma_k * Identity;
        Vecteur<double> z = H_k0 * q;
        if(k>0){
            for (int i = k - m; i <= k - 1; i++)
            {
                if (i % m < 0)
                {
                    indice = i % m + m;
                }
                else
                {
                    indice = i % m;
                }
                rho_i = 1 / (y[indice] | s[indice]);
                beta_k(indice + 1) = rho_i * y[indice] | z;
                z = z + s[indice] * (alpha_k(indice + 1) - beta_k(indice + 1));
            }
        }
        z *= -1; // z est la direction de descente d_k = -H_k*g_k
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe(Image, x, z, g_k);
        x_new = x + z * alpha;
        y[k % m] = toVecteur(grad_fonctionnelle(Image, x_new)) - toVecteur(grad_fonctionnelle(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;
    }
    cout << "Norme du Gradient : " << toVecteur(grad_fonctionnelle(Image, x)).norm() << endl;
    cout << "L'algorithme n'a pas convergé en " << i_max << " itérations " << endl;
    // detruit tout avant de return
    return x;
}

// BFGS Hauteur

Vecteur<double> BFGS_hauteur(const Matrice &Image, Vecteur<double> &x)
{

    Matrice Identity(x.dim,x.dim, 0);
    Identity.ToIdentity();
    Vecteur<double> x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 7;
    vector<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    vector<Vecteur<double>> y(m);
    for (int i = 0; i < m; i++)
    {
        s[i].init(x.dim, 0.01);
        y[i].init(x.dim, 0.01);
    }
    Vecteur<double> alpha_k(m, 0);
    Vecteur<double> beta_k(m, 0);
    double gamma_k = 1;
    double beta_i = 0;
    double alpha = 0;
    int k = 0;
    int indice = 0;
    while (k < i_max)
    {
        // VOIR WIKIPEDIA POUR LE MODÈLE

        // Calcul du gradient de la fonctionnelle
        Vecteur<double> g_k = toVecteur(grad_fonctionnelle_hauteur(Image, x));
        cout << "Itérations : " << k << endl;
        cout << "Norme du Gradient : " << g_k.norm() << endl;
        cout << "Fonctionnelle : " << fonctionnelle_hauteur(Image,x) << endl;
        // getchar();
        // Test de la condition 
        if (g_k.norm() < epsilon_2)
        {
            return x;
        }

        Vecteur<double> q = g_k;
        double rho_i = 0;
        if(k>0){
            for (int i = k - 1; i >= k - m; i--)
            {
                if (i % m < 0)
                {
                    indice = i % m + m;
                }
                else
                {
                    indice = i % m;
                }
                rho_i = 1 / (y[indice] | s[indice]);
                alpha_k(indice + 1) = rho_i * s[indice] | q;
                q = q - alpha_k(indice + 1) * y[indice];
            }
        }
        if (k > 0) // valeur Nan si on ne mets pas k>0
        {   
            // Définition de Gamma
            gamma_k = (s[(k - 1) % m] | y[(k - 1) % m]) / (y[(k - 1) % m] | y[(k - 1) % m]);
        }
        Matrice H_k0 = gamma_k * Identity;
        Vecteur<double> z = H_k0 * q;
        if(k>0){
            for (int i = k - m; i <= k - 1; i++)
            {
                if (i % m < 0)
                {
                    indice = i % m + m;
                }
                else
                {
                    indice = i % m;
                }
                rho_i = 1 / (y[indice] | s[indice]);
                beta_k(indice + 1) = rho_i * y[indice] | z;
                z = z + s[indice] * (alpha_k(indice + 1) - beta_k(indice + 1));
            }
        }

        z *= -1; // z est la direction de descente d_k = -H_k*g_k
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe_hauteur(Image, x_new, z, g_k);
        x_new = x + z * alpha;

        y[k % m] = toVecteur(grad_fonctionnelle_hauteur(Image, x_new)) - toVecteur(grad_fonctionnelle_hauteur(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;
    }
    return x;
}


//