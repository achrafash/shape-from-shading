from PIL import Image
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator
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
    return array


def othmane(n):
    array = np.zeros([n, n], dtype=np.uint8)

    for i in range(n//4, 3*n//4):
        for j in range(n//4, 3*n//4):
            value = 2 * (n/2) ** 2 - (i - n/2)**2 - (j - n/2)**2
            array[i, j] = value
    print(array)

    # Use PIL to create an image from the new array of pixels
    new_image = Image.fromarray(array)
    new_image.save('othmane.png')
    return array


def double_sin(n):
    image = np.zeros([n, n], dtype=np.uint8)

    for i in range(n):
        for j in range(n):
            image[i, j] = int(
                (np.sin(np.pi * i/n) + np.sin(np.pi * j/n)) * 255/2)

    new_image = Image.fromarray(image)
    new_image.save("double_sin.png")
    print("image saved!")
    return image


def cubic_difference(n):
    image = np.zeros([n, n], dtype=np.uint8)

    for i in range(n):
        for j in range(n):
            image[i, j] = int(((i/n)**3 - (j/n)**3)*255/2)

    new_image = Image.fromarray(image)
    new_image.save("cubic_difference.png")
    print("image saved")
    return image


def polaire_sin(n):
    image = np.zeros([n, n], dtype=np.uint8)
    for i in range(n):
        for j in range(n):
            r = np.sqrt(i**2 + j**2)
            theta = 0 if i == 0 else np.arctan(j/i)
            image[i, j] = int(
                (r/n)**(2/3) * np.sin(2*theta/3) * 255)

    new_image = Image.fromarray(image)
    new_image.save("polaire_sin.png")
    print("image saved")
    return image


def plot_3d_surface(array):
    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    n = len(array)

    # Make data.
    X = np.arange(0, n, 1)
    Y = X
    X, Y = np.meshgrid(X, Y)
    # R = np.sqrt(X**2 + Y**2)
    # Z = np.sin(R)

    # Plot the surface.
    surf = ax.plot_surface(X, Y, array, cmap=cm.coolwarm,
                           linewidth=0, antialiased=False)

    # Customize the z axis.
    # ax.set_zlim(-1.01, 1.01)
    # ax.zaxis.set_major_locator(LinearLocator(10))
    # A StrMethodFormatter is used automatically
    # ax.zaxis.set_major_formatter('{x:.02f}')

    # Add a color bar which maps values to colors.
    fig.colorbar(surf, shrink=0.5, aspect=5)

    plt.show()
    return 0


if __name__ == "__main__":
    array = polaire_sin(120)
    plot_3d_surface(array)
