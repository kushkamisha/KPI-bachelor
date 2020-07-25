import matplotlib.pyplot as plt
import numpy as np


def f1(x):
    """Calculates function 1 value in point x"""
    return (x + 1)**3 - x


def f2(x):
    """Calculates function 2 value in point x"""
    return x**3 + 0.2 * x**2 + 0.5 * x + 0.8


def main():
    t = np.arange(-5., 5., 0.2)

    # function
    plt.plot(t, f1(t))
    plt.plot(t, t * 0) # x[-2.5, -2]
    # plt.plot(t, f2(t))
    # plt.plot(t, t * 0) # x[-1, -0.7]

    plt.ylim([-20, 20])
    plt.xlim([-20, 20])
    plt.show()


if __name__ == "__main__":
    main()