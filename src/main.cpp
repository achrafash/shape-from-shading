#include <iostream>
#include "/home/othmane/shape/shape-from-shading/include/matrice.hpp"
#include "/home/othmane/shape/shape-from-shading/include/conversion_image_matrice.hpp"

int main(int argc, char *argv[]){
	
	// charger une image, la convertir en fichier .csv et créer une matrice image et la remplir des niveaux de gris de l'image initiale.

	// Done by achraf


	// Faire une boucle et appeler le code GBFS

	// Appel de la Méthode L-BFGS

	Matrice m = image_to_matrice("lib/dragon.csv");

	// Excellent maintenant, on peut travailler
	
	m.print();
	return 0;
}