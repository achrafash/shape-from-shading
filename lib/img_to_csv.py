from PIL import Image  # Importation du module
import csv  # Importation du package csv
import numpy as np  # Importation de numpy
import sys


def flatten(liste):
    flat_list = []
    for i in range(len(liste)):
        ligne = []
        for j in range(len(liste[i])):
            ligne.append(liste[i][j][0])
        flat_list.append(ligne)
    return flat_list


def img_to_csv(filename, array):
    list_array = array.tolist()
    list_array = flatten(list_array)
    print(len(list_array))
    print(len(list_array[0]))
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=',',
                            quotechar='"', quoting=csv.QUOTE_MINIMAL)
        writer.writerow([len(list_array), len(list_array[0])])
        writer.writerows(list_array)


def main(input_filename, output_filename):
    # Ouverture de l'image
    img = Image.open(input_filename).convert('LA')
    img_to_csv(output_filename, np.array(img))


if __name__ == "__main__":
    print(f"Arguments count: {len(sys.argv)}")
    if(len(sys.argv) != 3):
        print("Error: please provide input filename and output filename")
    else:
        main(sys.argv[1], sys.argv[2])
