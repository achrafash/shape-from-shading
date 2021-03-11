#include <iostream>
#include "matrice.hpp"
#include "conversion_image_matrice.hpp"
#include "vecteur.hpp"
#include "lbfgs.hpp"
#include "maillage.hpp"

//  g++ -o main.exe -Iinclude -Isrc src/main.cpp src/matrice.cpp src/conversion_image_matrice.cpp src/vecteur.cpp src/lbfgs.cpp src/maillage.cpp

int main(int argc, char *argv[])
{

	// On charge une image, et converti en fichier .csv et on crée une matrice image 
	// On la remplit avec les niveaux de gris de l'image initiale.
	// Done by achraf

	Matrice Image = image_to_matrice(argv[1]);
	// Image.print();

	// Appel de la Méthode L-BFGS
	// Définition de x=(p,q) initiale
	Vecteur<double> x0(2 * Image.n * Image.m, 0.5);

	cout << " BFGS Algorithme " << endl;
	// Appel de la Méthode L-BFGS
	Vecteur<double> x = BFGS(Image, x0,"normal");

	// Définition de la hauteur initiale
	Vecteur<double> h0(Image.n * Image.m, 0);

	// Définition de (p*,q*) sortant du BFGS

	Matrice etoile_pq = x.toMatrice(2 * Image.n, Image.m);
	// Matrice etoile_pq(2*Image.n,Image.m,5);
	cout << " BFGS Hauteur Algorithme " << endl;

	Vecteur<double> h_final = BFGS(etoile_pq, h0,"hauteur");

	Matrice result = h_final.toMatrice(Image.n, Image.m);

	cout << "Fini" << endl;
	cout << "Génération du maillage... "<< endl; 
	generate_mesh(result,argv[2]); // Génération du maillage
	
	return 0;
}