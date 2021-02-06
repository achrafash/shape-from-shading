#include "/home/othmane/shape/shape-from-shading/include/lbfgs.hpp"
#include <cmath>


// Ce code calcul la fonctionnelle e 
// Nous allons calculer la valeur de chaque fonctionnelle puis on fera la somme

double fonctionnelle(const Matrice& image,const Vecteur<double>& x){
    double e1 = 0,e2 = 0, e3 = 0;
    int n_ligne = image.n;
    int n_colonne = image.m;
    Matrice p = x(0, n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);
    Matrice q = x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);

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

Matrice grad_fonctionnelle(const Matrice& image,const Vecteur<double>& x){
    int n_ligne = image.n;
    int n_colonne = image.m;

    Matrice p = x(0, n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);
    Matrice q = x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);


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
        for(int j=1;j<=n_ligne;j++){

            e1(i,j) = 2 * 255 * (image(i-n_ligne,j)*sqrt(1+pow(p(i-n_ligne,j),2)+pow(q(i-n_ligne,j),2))-255)*(q(i-n_ligne,j)/pow(1+pow(p(i-n_ligne,j),2)+pow(q(i-n_ligne,j),2),2));
            e2(i,j) = 0; // calcul à faire
            e3(i,j) = 0;
        }
    }
    e1*=delta*delta;
    e2*=lambda_int;
    e3*=lambda_csmo;

    // coder l'opérateur + pour return delta*delta*e1+lambda_int*e2+...
    cout << "oui_grad_fonctionnelle" << endl;
    return e1+e2+e3;

}


// Ce code calcul la fonctionnelle hauteur

double fonctionnelle_hauteur(const Matrice& h, const Vecteur<double>& x){
    double result = 0;
    int n_ligne = h.n;
    int n_colonne = h.m;

    Matrice p = x(0, n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);
    Matrice q = x(n_ligne * n_colonne, 2 * n_ligne * n_colonne - 1).toMatrice(n_ligne, n_colonne);

    for(int i=1;i<n_ligne;i++){
        for(int j=1;j<n_colonne;j++){
               result += pow((h(i+1,j)-h(i,j)-delta*p(i,j)),2)+pow(h(i,j+1)-h(i,j)-delta*q(i,j),2);
        }
    }

    return result;
}

// J'AI RECOPIÉ 
Vecteur<double> grad_fonctionnelle_hauteur(const Matrice & Image, Vecteur<double> &h)
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
	return toVecteur(gradient * 2);
}



// Ce code calcul le gradient de la fonctionnelle discrétisée pour retrouver la hauteur
// Nous allons calculer les gradients de chaque fonctionnelle puis on fera la somme

double Wolfe(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient){

    int i = 0;
    double alpha = 1;
    Vecteur<double> x_new = x + alpha * z;
    double e_new = fonctionnelle(Image,x_new);
    double e = fonctionnelle(Image,x);
    double grad_e_pk = gradient*z;
    Vecteur<double> grad_e_new = toVecteur(grad_fonctionnelle(Image, x_new));

    while(((e_new>e+w1*alpha*grad_e_pk || abs(grad_e_new*z))>w2*abs(grad_e_pk)) && (i<i_max)){
        i++;
        alpha /= 2;
        x_new = x + alpha * z;
        e_new = fonctionnelle(Image,x_new);
        grad_e_new = toVecteur(grad_fonctionnelle(Image, x_new));
    }
    return alpha;

}
 
// Méthode BFGS

Vecteur<double> BFGS(const Matrice& Image,Vecteur<double>& x){
    Matrice_diag Identity(x.dim,1);
    cout << "oui" << endl;
    Vecteur<double> x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 4;
    vector<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    // Vecteur<double> initial(x.dim, 1);
    vector<Vecteur<double>> y(m); 
    for(int i=0;i<m;i++){
        s[i].init(x.dim,1);
        y[i].init(x.dim,1);
    }
    Vecteur<double> alpha_k(m, 0);
    Vecteur<double> beta_k(m, 0);
    double gamma_k = 0;
    double beta_i = 0;
    double alpha = 0;
    int k = 0;
    int indice = 0;
    while(k<i_max){
        // VOIR WIKIPEDIA POUR LE MODÈLE
        cout << "oui" << endl;
        // Calcul du gradient de la fonctionnelle
        Vecteur<double> g_k = toVecteur(grad_fonctionnelle(Image, x));
        cout << "oui" << endl;
        // Test de la condition
        if(g_k.norm()<epsilon){
            return x_new;
        }
        Vecteur<double> q = g_k;
        cout << "oui" << endl;
        double rho_i = 0;
        for(int i=k-1;i>=k-m;i--){
            if(i%m<0){
                indice = i%m+m;
            }
            else{
                indice = i%m;
            }
            rho_i = 1/(y[indice]*s[indice]);
            cout << "oui_2" << endl;
            alpha_k(indice)= rho_i*s[indice]*q;
            cout << "oui_2" << endl;
            printf("dimension q : %d , dimension alpha_k : %d, dimension y : %d , indice %d \n",q.dim,alpha_k.dim,y[indice].dim,indice);
            q = q-alpha_k(indice)*y[indice];
            cout << "oui" << endl;
        }
        cout << "oui" << endl;
        gamma_k = (s[(k-1)%m]*y[(k-1)%m])/(y[(k-1)%m]*y[(k-1)%m]);
        Matrice_diag H_k0 = gamma_k*Identity;
        Vecteur<double> z = H_k0 * q;
        cout << "oui" << endl;
        for(int i=k-m;i<=k-1;i++){
            if(i%m<0){
                indice = i%m+m;
            }
            else{
                indice = i%m;
            }
            rho_i = 1/(y[indice]*s[indice]);
            beta_k(indice)= rho_i*y[indice]*z;
            z = z + s[indice]*(alpha_k(indice)-beta_k(indice));
        }
        cout << "oui" << endl;
        z*=-1; // z est la direction de descente d_k = -H_k*g_k

        
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe(Image,x_new,z, g_k);
        x_new = x + z * alpha;

        y[k % m] = toVecteur(grad_fonctionnelle(Image,x_new)) - toVecteur(grad_fonctionnelle(Image,x));
        s[k % m] = x_new-x;
        x = x_new;
        k++;
    }
    cout << "Norme du Gradient : "<< toVecteur(grad_fonctionnelle(Image, x)).norm()<<endl;
    cout << "L'algorithme n'a pas convergé en" << i_max << " itérations " <<endl; 
    return x;
}

double Wolfe_hauteur(const Matrice& Image, Vecteur<double>& x, Vecteur<double>& z, Vecteur<double>& gradient){

    int i = 0;
    double alpha = 1;
    Vecteur<double> x_new = x + alpha * z;
    double e_new = fonctionnelle_hauteur(Image,x_new);
    double e = fonctionnelle_hauteur(Image,x);
    double grad_e_pk = gradient*z;
    Vecteur<double> grad_e_new = grad_fonctionnelle_hauteur(Image, x_new);

    while(((e_new>e+w1*alpha*grad_e_pk || abs(grad_e_new*z))>w2*abs(grad_e_pk)) && (i<i_max)){
        i++;
        alpha /= 2;
        x_new = x + alpha * z;
        e_new = fonctionnelle_hauteur(Image,x_new);
        grad_e_new = grad_fonctionnelle_hauteur(Image, x_new);
    }
    return alpha;

}


Vecteur<double> BFGS_hauteur(const Matrice& Image,Vecteur<double>& x){

    Matrice_diag Identity(x.dim,1);
    Vecteur<double> x_new = x;
    int n_ligne = Image.n;
    int m_colonne = Image.m;
    int m = 4;
    vector<Vecteur<double>> s(m); // vecteur de vecteur de s allant de k-1 à k-m
    vector<Vecteur<double>> y(m); 
    Vecteur<double> alpha_k(m, 0);
    Vecteur<double> beta_k(m, 0);
    double gamma_k = 0;
    double beta_i = 0;
    double alpha = 0;
    int k = 0;
    int indice = 0;
    while(k<i_max){
        // VOIR WIKIPEDIA POUR LE MODÈLE

        // Calcul du gradient de la fonctionnelle
        Vecteur<double> g_k = grad_fonctionnelle_hauteur(Image, x_new);

        // Test de la condition
        if(g_k.norm()<epsilon){
            return x_new;
        }
        Vecteur<double> q = g_k;

        double rho_i = 0;
         for(int i=k-1;i>=k-m;i--){
            if(i%m<0){
                indice = i%m+m;
            }
            else{
                indice = i%m;
            }
            rho_i = 1/(y[indice]*s[indice]);
            cout << "oui_2" << endl;
            alpha_k(indice)= rho_i*s[indice]*q;
            cout << "oui_2" << endl;
            printf("dimension q : %d , dimension alpha_k : %d, dimension y : %d , indice %d \n",q.dim,alpha_k.dim,y[indice].dim,indice);
            q = q-alpha_k(indice)*y[indice];
            cout << "oui" << endl;
        }
        
        gamma_k = (s[(k-1)%m]*y[(k-1)%m])/(y[(k-1)%m]*y[(k-1)%m]);
        Matrice_diag H_k0 = gamma_k*Identity;
        Vecteur<double> z = H_k0 * q;

        for(int i=k-m;i<=k-1;i++){
            if(i%m<0){
                indice = i%m+m;
            }
            else{
                indice = i%m;
            }
            rho_i = 1/(y[indice]*s[indice]);
            beta_k(indice)= rho_i*y[indice]*z;
            z = z + s[indice]*(alpha_k(indice)-beta_k(indice));
        }

        z*=-1; // z est la direction de descente d_k = -H_k*g_k

        
        // Calcul du pas alpha respectant la condition de Wolfe
        alpha = Wolfe_hauteur(Image,x_new,z, g_k);
        x_new = x + z * alpha;

        y[k % m] = grad_fonctionnelle_hauteur(Image,x_new) - grad_fonctionnelle_hauteur(Image,x);
        s[k % m] = x_new- x;
        x = x_new;
        k++;
    }


}
