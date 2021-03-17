# Shape from shading
# Execution
```
g++ -o main.exe -Iinclude -Isrc src/*.cpp
```

Pour générer des images en niveaux de gris au format csv
```
cd lib
python img_to_csv <<input_img>> <<output_csv>>
```

#### Execution
Retourner et la racine
```
./main.exe <<input_csv>> <<output_mesh>>
```

## Description
Find a code allowing you to transform your image into a 3D surface.
#### Librairies

- Algorithme BFGS

#### Installation

Install Vizir to Visualize the result

## Compile

```
g++ -o main -Iinclude -Isrc src/main.cpp src/matrice.cpp src/conversion_image_matrice.cpp
```

g++ src/main.cpp src/conversion_image_matrice.cpp src/matrice.cpp src/vecteur.cpp src/lbfgs.cpp -o main.exe