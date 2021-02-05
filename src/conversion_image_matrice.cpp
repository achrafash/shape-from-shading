#include "/home/othmane/shape/shape-from-shading/include/conversion_image_matrice.hpp"

// IL faut convertir notre image en matrice

// l'intermédiaire c'est le csv 

Matrice image_to_matrice(string nom_fichier){

    ifstream image(nom_fichier.c_str(),ios::in);
    int n = 0;
    int m = 0;
    string line;
    if (image.is_open())
  {
      image>>n;
      image>>m;
      printf("n = %d, m = %d",n,m);
    while ( getline (image,line) )
    {
      // std::cout << line << '\n';
    }
    image.close();
  }

  else cout << "Unable to open file"; 

    Matrice Image(n,m);

    return Image;

}