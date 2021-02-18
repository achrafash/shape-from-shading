#include "maillage.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Cette fonction génère le maillage  à partir de la matrice surface M.
// Elle prend en compte le nom du maillage

void generate_mesh(const Matrice &M,const string& name_mesh)
{
    std::ofstream outfile(name_mesh);
    outfile << "MeshVersionFormatted 2" << std::endl
            << "Dimension 3" << std::endl
            << "# Set of mesh vertices (x,y,h(x,y),ref)" << std::endl
            << "Vertices" << std::endl
            << M.n * M.m << std::endl;
    // Sommets
    for (int i = 1; i <= M.n; i++)
    {
        for (int j = 1; j <= M.m; j++)
        {
            outfile << i
                    << " " << j
                    << " " << M(i, j)
                    << " " << 0 << std::endl;
        }
    }

    outfile << "# Set of mesh quads (v1,v2,v3,v4,ref)" << std::endl
            << "Quadrilaterals" << std::endl
            << (M.n - 1) * (M.m - 1) << std::endl;
    // Quadrangles
    for (int i = 1; i <= M.n - 1; i++)
    {
        for (int j = 1; j <= M.m - 1; j++)
        {
            outfile << i + (j-1)*M.n
                    << " " << i + 1 + (j-1)*M.n
                    << " " << i + 1 + j*M.n
                    << " " << i + j*M.n 
                    << " " << 0 << std::endl;
        }
    }

    outfile << "End" << std::endl;

    outfile.close();
}