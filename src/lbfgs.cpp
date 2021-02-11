#include "lbfgs.hpp"
#include <cmath>

// Ce code calcul la fonctionnelle e
// Nous allons calculer la valeur de chaque fonctionnelle puis on fera la somme

double fonctionnelle(const Matrice &image, const Vecteur<double> &x)
{
    double e1 = 0, e2 = 0, e3 = 0;
    int n_ligne = image.n;
    int n_colonne = image.m;
    Matrice p = x(0, n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);
    Matrice q = x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);

    for (int i = 1; i <= n_ligne; i++)
    {
        for (int j = 1; j <= n_colonne; j++)
        {
            e1 += pow(image(i, j) - 255 / sqrt(1 + pow(p(i, j), 2) + pow(q(i, j), 2)), 2);
            // si (i,j) est dans le domaine D1
            if (i != n_colonne && j != n_ligne)
            {
                e2 += pow((p(i, j + 1) - p(i, j)) - (q(i + 1, j) - q(i, j)), 2);
                e3 += pow(p(i + 1, j) - p(i, j), 2) + pow(p(i, j + 1) - p(i, j), 2) + pow(q(i + 1, j) - q(i, j), 2) + pow(q(i, j + 1) - q(i, j), 2);
            }
        }
    }

    return delta * delta * e1 + lambda_int * e2 + lambda_csmo * e3;
}

// Ce code calcul le gradient de la fonctionnelle e
// Nous allons calculer les gradients de chaque fonctionnelle puis on fera la somme

Matrice grad_fonctionnelle(const Matrice &image, const Vecteur<double> &x)
{
    int n_ligne = image.n;
    int n_colonne = image.m;

    Matrice p = x(0, n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);
    Matrice q = x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);

    // Matrice result(2*n_ligne,n_colonne);
    Matrice e1(2 * n_ligne, n_colonne);
    Matrice e2(2 * n_ligne, n_colonne);
    Matrice e3(2 * n_ligne, n_colonne);

    for (int i = 1; i <= n_ligne; i++)
    {
        for (int j = 1; j <= n_colonne; j++)
        {

            e1(i, j) = 2 * 255 * (image(i, j) * sqrt(1 + pow(p(i, j), 2) + pow(q(i, j), 2)) - 255) * (p(i, j) / pow(1 + pow(p(i, j), 2) + pow(q(i, j), 2), 2));
            if (i != 1 && j != 1 && i != n_ligne && j != n_colonne)
            {
                e2(i, j) = 2 * p(i, j) - p(i, j - 1) - p(i, j + 1) - q(i, j) + q(i + 1, j) - q(i + 1, j - 1) + q(i, j - 1);
                e3(i, j) = 4 * p(i, j) - p(i - 1, j) - p(i + 1, j) - p(i, j - 1) - p(i, j + 1);
            }
        }
    }

    for (int i = n_ligne + 1; i <= 2 * n_ligne; i++)
    {
        for (int j = 1; j <= n_ligne; j++)
        {

            e1(i, j) = 2 * 255 * (image(i - n_ligne, j) * sqrt(1 + pow(p(i - n_ligne, j), 2) + pow(q(i - n_ligne, j), 2)) - 255) * (q(i - n_ligne, j) / pow(1 + pow(p(i - n_ligne, j), 2) + pow(q(i - n_ligne, j), 2), 2));
            if (i != n_ligne + 1 && j != 1 && i != 2 * n_ligne && j != n_ligne)
            {
                e2(i, j) = 2 * q(i - n_ligne, j) - q(i - 1 - n_ligne, j) - q(i + 1 - n_ligne, j) - p(i - n_ligne, j) + p(i - n_ligne, j + 1) - p(i - 1 - n_ligne, j + 1) + p(i - 1 - n_ligne, j);
                e3(i, j) = 4 * q(i - n_ligne, j) - q(i - 1 - n_ligne, j) - q(i + 1 - n_ligne, j) - q(i - n_ligne, j - 1) - q(i - n_ligne, j + 1);
            }
        }
    }
    e1 *= delta * delta;
    e2 *= lambda_int;
    e3 *= lambda_csmo;

    // coder l'opérateur + pour return delta*delta*e1+lambda_int*e2+...
    // cout << "oui_grad_fonctionnelle" << endl;
    return e1 + e2 + e3;
}

// Ce code calcul la fonctionnelle hauteur

double fonctionnelle_hauteur(const Matrice &x, const Vecteur<double> &h)
{
    double result = 0;
    int n_ligne = x.n / 2;
    int n_colonne = x.m;
    Matrice hauteur = h.toMatrice(n_ligne, n_colonne);

    for (int i = 1; i < n_ligne; i++)
    {
        for (int j = 1; j < n_colonne; j++)
        {
            result += pow((hauteur(i + 1, j) - hauteur(i, j) - delta * x(i, j)), 2) + pow(hauteur(i, j + 1) - hauteur(i, j) - delta * x(i + n_ligne, j), 2);
        }
    }

    return result;
}

// 
Matrice grad_fonctionnelle_hauteur(const Matrice &Image, Vecteur<double> &h)
{
    int nb_l = Image.n / 2;
    int nb_c = Image.m;
    Matrice hauteur = h.toMatrice(nb_l, nb_c);
    Matrice gradient(nb_l, nb_c, 0);

    for (int i = 1; i < nb_l + 1; i++)
    {
        for (int j = 1; j < nb_c + 1; j++)
        {
            if (i != 1 && j != 1 && i != nb_l && j != nb_c)
            {
                gradient(i, j) = 4 * hauteur(i, j) - hauteur(i - 1, j) - delta * Image(i - 1, j) - hauteur(i + 1, j) + delta * Image(i, j) - hauteur(i, j - 1) - delta * Image(i + nb_l, j - 1) - hauteur(i, j + 1) + delta * Image(i + nb_l, j);
            }
        }
    }
    // cout << toVecteur(gradient);
    return 2 * gradient;
}

// Ce code calcul le gradient de la fonctionnelle discrétisée pour retrouver la hauteur
// Nous allons calculer les gradients de chaque fonctionnelle puis on fera la somme

double Wolfe(const Matrice &Image, Vecteur<double> &x, Vecteur<double> &z, Vecteur<double> &gradient)
{

    int i = 0;
    double alpha = 1;
    Vecteur<double> x_new = x + alpha * z;
    double e_new = fonctionnelle(Image, x_new);
    double e = fonctionnelle(Image, x);
    double grad_e_pk = gradient * z;
    Vecteur<double> grad_e_new = toVecteur(grad_fonctionnelle(Image, x_new));

    while(((e_new>e+w1*alpha*grad_e_pk || abs(grad_e_new*z))>w2*abs(grad_e_pk)) && (i<i_max_Wolfe)){
        i++;
        alpha /= 2;
        x_new = x + alpha * z;
        e_new = fonctionnelle(Image, x_new);
        grad_e_new = toVecteur(grad_fonctionnelle(Image, x_new));
    }
    return alpha;
}

// Méthode BFGS

Vecteur<double> BFGS(const Matrice &Image, Vecteur<double> &x)
{
    Matrice_diag Identity(x.dim, 1);
    cout << "oui" << endl;
    Vecteur<double> x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 6;
    vector<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    Vecteur<double> initial(x.dim, 1);
    vector<Vecteur<double>> y(m);
    for (int i = 0; i < m; i++)
    {
        s[i].init(x.dim, 0.1);
        y[i].init(x.dim, 0.1);
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
        // cout << "oui" << endl;
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
            rho_i = 1 / (y[indice] * s[indice]);
            // cout << "oui_2" << endl;
            alpha_k(indice + 1) = rho_i * s[indice] * q;
            // cout << "oui_2" << endl;
            // printf("dimension q : %d , dimension alpha_k : %d, dimension y : %d , indice %d \n",q.dim,alpha_k.dim,y[indice].dim,indice);
            q = q - alpha_k(indice + 1) * y[indice];
            // cout << "oui" << endl;
        }
        // cout << "oui" << endl;
        if (k > 0)
        {
            gamma_k = (s[(k - 1) % m] * y[(k - 1) % m]) / (y[(k - 1) % m] * y[(k - 1) % m]);
        }
        Matrice_diag H_k0 = gamma_k * Identity;
        Vecteur<double> z = H_k0 * q;
        // cout << "oui" << endl;
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
            rho_i = 1 / (y[indice] * s[indice]);
            beta_k(indice + 1) = rho_i * y[indice] * z;
            z = z + s[indice] * (alpha_k(indice + 1) - beta_k(indice + 1));
        }
        // cout << "oui" << endl;
        z *= -1; // z est la direction de descente d_k = -H_k*g_k

        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe(Image, x, z, g_k);
        x_new = x + z * alpha;

        y[k % m] = toVecteur(grad_fonctionnelle(Image, x_new)) - toVecteur(grad_fonctionnelle(Image, x));
        s[k % m] = x_new - x;
        x = x_new;
        k++;
    }
    // cout << toVecteur(grad_fonctionnelle(Image, x)) <<endl;
    cout << "Norme du Gradient : " << toVecteur(grad_fonctionnelle(Image, x)).norm() << endl;
    cout << "L'algorithme n'a pas convergé en " << i_max << " itérations " << endl;
    cout << "problem" << endl;
    /*
    for(int i=0;i<m;i++){
        s[i].clear();
        y[i].clear();
    }
    */
    // beta_k alpha_k Identity xnew g_k q z Hk_0
    /*
    cout << "nouveaux" << endl;
    Vecteur<double> nouveaux(2, 1.0);
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

double Wolfe_hauteur(const Matrice &Image, Vecteur<double> &x, Vecteur<double> &z, Vecteur<double> &gradient)
{

    int i = 0;
    double alpha = 1;
    // cout << "Wolfe "<<endl;
    Vecteur<double> x_new = x + alpha * z;
    double e_new = fonctionnelle_hauteur(Image, x_new);
    // cout << "Wolfe "<<endl;
    double e = fonctionnelle_hauteur(Image, x);
    double grad_e_pk = gradient * z;
    Vecteur<double> grad_e_new = toVecteur(grad_fonctionnelle_hauteur(Image, x_new));
    // cout << "Wolfe "<<endl;
    while(((e_new>e+w1*alpha*grad_e_pk || abs(grad_e_new*z))>w2*abs(grad_e_pk)) && (i<i_max_Wolfe)){
        i++;
        alpha /= 2;
        x_new = x + alpha * z;
        e_new = fonctionnelle_hauteur(Image, x_new);
        grad_e_new = toVecteur(grad_fonctionnelle_hauteur(Image, x_new));
    }
    // cout << "alpha " << alpha << endl;
    return alpha;
}

Vecteur<double> BFGS_hauteur(const Matrice &Image, Vecteur<double> &x)
{

    Matrice_diag Identity(x.dim, 1);
    Vecteur<double> x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 8;
    vector<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    vector<Vecteur<double>> y(m);
    for (int i = 0; i < m; i++)
    {
        s[i].init(x.dim, 0.1);
        y[i].init(x.dim, 0.1);
    }
    Vecteur<double> alpha_k(m, 0);
    Vecteur<double> beta_k(m, 0);
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
        Vecteur<double> g_k = toVecteur(grad_fonctionnelle_hauteur(Image, x));
        // cout << x.norm() <<endl;
        cout << "Itérations : " << k << endl;
        cout << "Norme du Gradient : " << g_k.norm() << endl;
        // Test de la condition
        if (g_k.norm() < epsilon_2)
        {
            return x;
        }
        // cout << "oui 2"<<endl;

        Vecteur<double> q = g_k;

        double rho_i = 0;
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
            rho_i = 1 / (y[indice] * s[indice]);
            // cout << "oui_2" << endl;
            alpha_k(indice + 1) = rho_i * s[indice] * q;

            // cout << "oui_2" << endl;
            // printf("dimension q : %d , dimension alpha_k : %d, dimension y : %d , indice %d \n",q.dim,alpha_k.dim,y[indice].dim,indice);
            q = q - alpha_k(indice + 1) * y[indice];
            // cout << "oui" << endl;
        }
        // cout << alpha_k;
        // if(k==0){cout << q;}
        // valeur nan si on ne mets pas k>0
        if (k > 0)
        {
            gamma_k = (s[(k - 1) % m] * y[(k - 1) % m]) / (y[(k - 1) % m] * y[(k - 1) % m]);
        }
        // cout << "Gamma_k" << gamma_k <<endl;
        Matrice_diag H_k0 = gamma_k * Identity;
        Vecteur<double> z = H_k0 * q;
        // if(k==0){cout << z;}

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
            rho_i = 1 / (y[indice] * s[indice]);
            beta_k(indice + 1) = rho_i * y[indice] * z;
            z = z + s[indice] * (alpha_k(indice + 1) - beta_k(indice + 1));
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
