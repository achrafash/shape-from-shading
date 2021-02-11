from PIL import Image
import csv
import numpy as np

img = Image.open('../images/sphere_2.png').convert('LA')
img.save('greyscale.png')

img = np.array(Image.open("greyscale.png"))

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
    with open(filename + '.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=',',quotechar='"', quoting=csv.QUOTE_MINIMAL)
        writer.writerow([len(list_array),len(list_array[0])])
        writer.writerows(list_array)
   
img_to_csv("image", img)