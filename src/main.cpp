#include <iostream>
#include "matrice.hpp"
#include "conversion_image_matrice.hpp"

int main(int argc, char *argv[])
{
	// charger une image, la convertir en fichier .csv et créer une matrice image et la remplir des niveaux de gris de l'image initiale.

	// Done by achraf
	Matrice M;
	M = image_to_matrice("lib/image.csv");
	M.print();

	// Faire une boucle et appeler le code GBFS

	// Méthode L-BFGS

	// float w1 = 10e-6;
	// float w2 = 10e-6;
	// float epsilon = 10e-6;

	// int n = 100;
	// int m = 100;

	// Matrice p(n,m);
	// Matrice q(n,m);

	// Matrice W1(n,m);

	return 0;
}