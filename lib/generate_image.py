from PIL import Image
import numpy as np


def parabole(n):
    array = np.zeros([n, n], dtype=np.uint8)

    for i in range(n):
        for j in range(n):
            value = abs((np.sin(i/10) + np.sin(j/10)) / 2)
            value = int(150*value + 50)
            array[i, j] = value
    print(array)

    # Use PIL to create an image from the new array of pixels
    new_image = Image.fromarray(array)
    new_image.save('parabole.png')
    return "done!"


parabole(64)
