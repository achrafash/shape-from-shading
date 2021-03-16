#include "lbfgs.hpp"
#include <cmath>

// Méthode BFGS

Vecteur BFGS(const Matrice &Image, Vecteur &x)
{
    Matrice Identity(x.dim,x.dim, 0);
    Identity.ToIdentity();
    cout << "oui" << endl;
    Vecteur x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 5;
    vector<Vecteur> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    Vecteur initial(x.dim, 1); // vecteur de vecteur de s allant de k-1 à k-m
    vector<Vecteur> y(m); 
    for (int i = 0; i < m; i++)
    {
        s[i].init(x.dim, 0.01); 
        y[i].init(x.dim, 0.01);
    }
    Vecteur alpha_k(m, 0);
    Vecteur beta_k(m, 0);
    double gamma_k = 1; 
    double beta_i = 0;
    double alpha = 0;
    int k = 0; // Itérateur
    int indice = 0; 
    while (k < i_max)
    {
        // VOIR WIKIPEDIA POUR LE MODÈLE
        // cout << "oui" << endl;
        // Calcul du gradient de la fonctionnelle
        // cout << "oui"<<endl;
        Vecteur g_k = toVecteur(grad_fonctionnelle(Image, x));
        cout << "Itérations : " << k << endl;
        cout << "oui, norme du gradient : " << g_k.norm() << endl;
        // Test de la condition 
        if (g_k.norm() < epsilon_1)
        {
            return x;
        }
        Vecteur q = g_k;
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
                // cout << "oui_2" << endl;
                alpha_k(indice + 1) = rho_i * s[indice] | q;
                // cout << "oui_2" << endl;
                // printf("dimension q : %d , dimension alpha_k : %d, dimension y : %d , indice %d \n",q.dim,alpha_k.dim,y[indice].dim,indice);
                q = q - alpha_k(indice + 1) * y[indice];
                // cout << "oui" << endl;
            }
        }
        // cout << "oui" << endl;
        if (k > 0)
        {
            // mise à jour de Gamma
            gamma_k = (s[(k - 1) % m] | y[(k - 1) % m]) / (y[(k - 1) % m] | y[(k - 1) % m]);
        }
        Matrice H_k0 = gamma_k * Identity;
        Vecteur z = H_k0 * q;
        // cout << "oui" << endl;
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
        // cout << "oui" << endl;
        z *= -1; // z est la direction de descente d_k = -H_k*g_k
        // cout << "Wolfe" <<endl;
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe(Image, x, z, g_k);
        x_new = x + z * alpha;
        // cout << "Wolfe fini" <<endl;

        y[k % m] = toVecteur(grad_fonctionnelle(Image, x_new)) - toVecteur(grad_fonctionnelle(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;
    }
    // cout << toVecteur(grad_fonctionnelle(Image, x)) <<endl;
    cout << "Norme du Gradient : " << toVecteur(grad_fonctionnelle(Image, x)).norm() << endl;
    cout << "L'algorithme n'a pas convergé en " << i_max << " itérations " << endl;
    // cout << "problem" << endl;
    /*
    for(int i=0;i<m;i++){
        s[i].clear();
        y[i].clear();
    }
    */
    // beta_k alpha_k Identity xnew g_k q z Hk_0
    /*
    cout << "nouveaux" << endl;
    Vecteur nouveaux(2, 1.0);
    nouveaux.clear();
    cout << "beta_k" << endl;
    for (int i = 1; i <= m; i++)
    {
        beta_k(i) = 0;
    }
    cout << beta_k;
    beta_k.clear();
    cout << "initial" << endl;
    initial.clear();
    cout << "alpha_k" << endl;
    cout << alpha_k;
    cout << "ouai" << endl;
    alpha_k.clear();
    */
    // detruit tout avant de return
    return x;
}

// BFGS Hauteur

Vecteur BFGS_hauteur(const Matrice &Image, Vecteur &x)
{

    Matrice Identity(x.dim,x.dim, 0);
    Identity.ToIdentity();
    Vecteur x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 7;
    vector<Vecteur> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    vector<Vecteur> y(m);
    for (int i = 0; i < m; i++)
    {
        s[i].init(x.dim, 0.01);
        y[i].init(x.dim, 0.01);
    }
    Vecteur alpha_k(m, 0);
    Vecteur beta_k(m, 0);
    double gamma_k = 1;
    double beta_i = 0;
    double alpha = 0;
    int k = 0;
    int indice = 0;
    cout << "oui 1" << endl;
    while (k < i_max)
    {
        // VOIR WIKIPEDIA POUR LE MODÈLE

        // Calcul du gradient de la fonctionnelle
        Vecteur g_k = toVecteur(grad_fonctionnelle_hauteur(Image, x));
        // cout << x.norm() <<endl;
        cout << "Itérations : " << k << endl;
        cout << "Norme du Gradient : " << g_k.norm() << endl;
        cout << "Fonctionnelle : " << fonctionnelle_hauteur(Image,x) << endl;
        // getchar();
        // Test de la condition 
        if (g_k.norm() < epsilon_2)
        {
            return x;
        }
        // cout << "oui 2"<<endl;

        Vecteur q = g_k;
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
                // cout << "oui_2" << endl;
                alpha_k(indice + 1) = rho_i * s[indice] | q;

                // cout << "oui_2" << endl;
                // printf("dimension q : %d , dimension alpha_k : %d, dimension y : %d , indice %d \n",q.dim,alpha_k.dim,y[indice].dim,indice);
                q = q - alpha_k(indice + 1) * y[indice];
                // cout << "oui" << endl;
            }
        }
        // cout << alpha_k;
        // if(k==0){cout << q;}
        // valeur nan si on ne mets pas k>0
        if (k > 0)
        {   
            // Définition de Gamma
            gamma_k = (s[(k - 1) % m] | y[(k - 1) % m]) / (y[(k - 1) % m] | y[(k - 1) % m]);
        }
        // cout << "Gamma_k" << gamma_k <<endl;
        Matrice H_k0 = gamma_k * Identity;
        Vecteur z = H_k0 * q;
        // if(k==0){cout << z;}
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

        // cout << "oui 5 "<<endl;
        // cout << z;
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe_hauteur(Image, x_new, z, g_k);
        x_new = x + z * alpha;
        // cout << "oui 6"<<endl;
        y[k % m] = toVecteur(grad_fonctionnelle_hauteur(Image, x_new)) - toVecteur(grad_fonctionnelle_hauteur(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;
        // cout << "oui"<<endl;
    }
    /*
    cout << "yes" <<endl;
    cout << "Norme du Gradient : "<< toVecteur(grad_fonctionnelle_hauteur(Image, x)).norm() <<endl;
    cout << "L'algorithme n'a pas convergé en " << i_max << " itérations " <<endl; 
    cout << "beta_k" <<endl;
    for(int i=1;i<=m;i++){
        beta_k(i) = 0;
    }
    cout << beta_k;
    beta_k.clear();
    cout << "alpha_k" <<endl;
    cout << alpha_k ;
    cout << "ouai"<< endl;
    alpha_k.clear();
    */
    return x;
}


//