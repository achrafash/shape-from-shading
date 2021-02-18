#include <iostream>
#include "matrice.hpp"
#include "conversion_image_matrice.hpp"
#include "vecteur.hpp"
#include "lbfgs.hpp"
#include "maillage.hpp"

//  g++ -o main.exe -Iinclude -Isrc src/main.cpp src/matrice.cpp src/conversion_image_matrice.cpp src/vecteur.cpp src/lbfgs.cpp src/maillage.cpp

int main(int argc, char *argv[])
{

	// charger une image, la convertir en fichier .csv et créer une matrice image et la remplir des niveaux de gris de l'image initiale.

	// Done by achraf
	Matrice Image = image_to_matrice(argv[1]);
	// Image.print();

	// Faire une boucle et appeler le code GBFS

	// Appel de la Méthode L-BFGS

	// Excellent maintenant, on peut travailler
	Vecteur<double> x0(2 * Image.n * Image.m, 0.5);

	cout << " BFGS Algorithme " << endl;

	Vecteur<double> x = BFGS(Image, x0);

	// cout << "Convergence" << endl;

	Vecteur<double> h0(Image.n * Image.m, 0);

	Matrice etoile_pq = x.toMatrice(2 * Image.n, Image.m);
	// Matrice etoile_pq(2*Image.n,Image.m,5);
	cout << " BFGS Hauteur Algorithme " << endl;

	Vecteur<double> h_final = BFGS_hauteur(etoile_pq, h0);

	Matrice result = h_final.toMatrice(Image.n, Image.m);

	cout << "Fini" << endl;
	cout << "Génération du maillage... " << endl;
	string output_file = argv[2];
	if (!argv[2])
	{
		output_file = "maillage.mesh";
	}
	generate_mesh(result, argv[2]);

	return 0;
}