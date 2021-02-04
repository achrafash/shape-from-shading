from PIL import Image
import csv
import numpy as np

img = Image.open('image.jpeg').convert('LA')
img.save('greyscale.png')

img = np.array(Image.open("greyscale.png"))

def img_to_csv(filename, array):
  list_array = array.tolist()
  with open(filename + '.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerows(list_array)

img_to_csv("image", img)