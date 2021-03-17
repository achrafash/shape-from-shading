#include "lbfgs.hpp"

// Méthode BFGS  pour la cas 1

Vecteur BFGS(const Matrice &Image, Vecteur &x){   

    Sparse Identity(x.dim,x.dim);
    Identity.Toidentity();

    Vecteur x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 5;
    Matrice s(m,x.dim,0.01); // vecteur de vecteur de s allant de k-1 à k-m
    Matrice y(m,x.dim,0.01); // vecteur de vecteur de y allant de k-1 à k-m
    Vecteur alpha_k(m, 0);
    Vecteur beta_k(m, 0);
    double gamma_k = 1; 
    double beta_i = 0;
    double alpha = 0;
    int k = 0; // Itérateur
    int indice = 0; 

    Vecteur g_k = toVecteur(grad_fonctionnelle(Image, x)); // Calcul du gradient de la fonctionnelle au point x 
    do{
        // VOIR WIKIPEDIA POUR LE MODÈLE
        // Calcul du gradient de la fonctionnelle
        g_k = toVecteur(grad_fonctionnelle(Image, x));
        cout << "Itérations : " << k << endl;
        cout << "oui, norme du gradient : " << g_k.norm() << endl;
        // Test de la condition 
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
                alpha_k(indice + 1) = rho_i * s[indice] | q;
                q = q - alpha_k(indice + 1) * y[indice];
            }
        }
        if (k > 0)
        {
            // mise à jour de Gamma
            gamma_k = (s[(k - 1) % m] | y[(k - 1) % m]) / (y[(k - 1) % m] | y[(k - 1) % m]);
        }
        Sparse H_k0 = gamma_k * Identity; // Définition de l'approximation diagonale de l'inverse du hessien 
        Vecteur z = H_k0 * q; // Direction de descente 
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
        z *= -1; // z est la direction de descente d_k = -H_k*g_k (dans le bon sens !!)
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe(Image, x, z, g_k);
        x_new = x + z * alpha;
        // cout << "Wolfe fini" <<endl;

        y[k % m] = toVecteur(grad_fonctionnelle(Image, x_new)) - toVecteur(grad_fonctionnelle(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;

        if(k>=i_max){
             cout << "L'algorithme n'a pas convergé en " << i_max << " itérations " <<endl; 
             exit(0);
        }


    }while(k < i_max && g_k.norm()>epsilon_1);

    cout << "L'algorithme a bien convergé en " << k << " itérations" << endl;

    return x;
}

// __________________________________________BFGS Hauteur_____________________________________________

Vecteur BFGS_hauteur(const Matrice &Image, Vecteur &x)
{

    Sparse Identity(x.dim,x.dim);
    //cout << "oui1" <<endl;
    Identity.Toidentity(); // Transformatio en matrice identité 
    Vecteur x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 7;
    Matrice s(m,x.dim,0.01); // vecteur de vecteur de s allant de k-1 à k-m
    Matrice y(m,x.dim,0.01); // vecteur de vecteur de y allant de k-1 à k-m
    Vecteur alpha_k(m, 0);
    Vecteur beta_k(m, 0);
    double gamma_k = 1;
    double beta_i = 0;
    double alpha = 0;
    int k = 0;
    int indice = 0;
    Vecteur g_k = toVecteur(grad_fonctionnelle_hauteur(Image, x));
    do{

        // VOIR WIKIPEDIA POUR LE MODÈLE

        // Calcul du gradient de la fonctionnelle
        g_k = toVecteur(grad_fonctionnelle_hauteur(Image, x));
        cout << "Itérations : " << k << endl;
        cout << "oui, norme du gradient : " << g_k.norm() << endl;
        // Test de la condition 

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
                alpha_k(indice + 1) = rho_i * s[indice] | q;
                q = q - alpha_k(indice + 1) * y[indice];
            }
        }
        // valeur nan si on ne mets pas k>0
        if (k > 0)
        {   
            // Définition de Gamma
            gamma_k = (s[(k - 1) % m] | y[(k - 1) % m]) / (y[(k - 1) % m] | y[(k - 1) % m]);
        }
        Sparse H_k0 = gamma_k * Identity;
        Vecteur z = H_k0 * q;
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
        // cout << "oui 6"<<endl;
        y[k % m] = toVecteur(grad_fonctionnelle_hauteur(Image, x_new)) - toVecteur(grad_fonctionnelle_hauteur(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;
        if(k>=i_max){
             cout << "L'algorithme n'a pas convergé en " << i_max << " itérations " <<endl; 
             exit(0);
        }

    } while (g_k.norm()>epsilon_2 && k<i_max) ;

    cout << "L'algorithme a bien convergé en " << k << " itérations" << endl;
    return x;
}
