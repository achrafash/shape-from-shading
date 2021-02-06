#include <iostream>
#include "/home/othmane/shape/shape-from-shading/include/matrice.hpp"
#include "/home/othmane/shape/shape-from-shading/include/conversion_image_matrice.hpp"
#include "/home/othmane/shape/shape-from-shading/include/vecteur.hpp"
#include "/home/othmane/shape/shape-from-shading/include/lbfgs.hpp"

int main(int argc, char *argv[]){
	
	// charger une image, la convertir en fichier .csv et créer une matrice image et la remplir des niveaux de gris de l'image initiale.

	// Done by achraf


	// Faire une boucle et appeler le code GBFS

	// Appel de la Méthode L-BFGS

	Matrice Image = image_to_matrice("lib/dragon.csv");

	// Excellent maintenant, on peut travailler

	Vecteur<double> x0(2*Image.n*Image.m,1);

	cout << " BFGS Algorithme " << endl;

	Vecteur<double> x = BFGS(Image,x0);

	cout << "OUI" <<endl;

	Vecteur<double> h0(Image.n * Image.m, 0);

	Matrice etoile_pq = x.toMatrice(2 * Image.n, Image.m);

	cout << " BFGS Hauteur Algorithme " << endl;

	Vecteur<double> h_final = BFGS_hauteur(etoile_pq,h0);

	Matrice result = h_final.toMatrice(Image.n,Image.m);



	return 0;
}