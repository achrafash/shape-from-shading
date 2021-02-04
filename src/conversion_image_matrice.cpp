#include "include/conversion_image_matrice.hpp"

// IL faut convertir notre image en matrice

// l'intermédiaire c'est le csv 

Matrice image_to_matrice(string nom_fichier){

    ifstream image(nom_fichier.c_str(),ios::in);
    
    int n = 0;
    int m = 0;
    image>>n;
    image>>m;

    Matrice Image(n,m);

    return Image;

}