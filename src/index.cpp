#include "conversion_image_matrice.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Matrice image_to_matrice(const char *filename)
{
    std::ifstream img_csv(filename);
    if (!img_csv.is_open())
        throw std::runtime_error("Could not open file");

    Matrice matrice(800, 800);

    std::string line;
    int val;

    int i = 1, j = 1;

    while (std::getline(img_csv, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);
        // Extract each integer
        while (ss >> val)
        {
            matrice(i, j) = val;
            // If the next token is a comma, ignore it and move on
            if (ss.peek() == ',')
                ss.ignore();
            j++;
        }
        i++;
        j = 1;
        std::cout << i << " " << j << std::endl;
    }

    img_csv.close();
    return matrice;
}