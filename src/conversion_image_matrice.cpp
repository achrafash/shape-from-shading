#include "conversion_image_matrice.hpp"

// IL faut convertir notre image en matrice

// l'intermédiaire c'est le csv

Matrice image_to_matrice(string nom_fichier)
{

    ifstream image(nom_fichier.c_str(), ios::in);

    int n = 0;
    int m = 0;
    string line;
    char virgule;
    if (image.is_open())
    {
        image >> n >> virgule >> m;
        // image>>m;
        Matrice Image(n, m);
        printf("n = %d, m = %d\n", n, m);
        int i(1), j(1);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                image >> Image(i, j) >> virgule;
            }
        }
        /*
    while ( getline (image,line) )
    {
      image>>Image(i,j)>>virgule;
      if(j==n)
      j++;
    }
    */
        image.close();
        return Image;
    }

    else
    {
        cout << "Unable to open file";
        exit(0);
    }
}