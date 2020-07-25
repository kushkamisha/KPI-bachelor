import math


def f(y):
    """Return value of a function"""
    return math.cos(0.4 * y + 4./3 * y**2 + 2./3) + 4./3 * y**2 + 2./3 + y**2 - 1.6


def x(y):
    """Returns x value for y"""
    return (4./3 * y**2 + 2./3)**(1/2)


def method_of_chords(a, b, epsilon):
    """
    Find the roots of equation
    using method of chords
    """
    c = 9999
    while abs(f(c)) >= epsilon and abs(b - a) >= epsilon:
        c = (a * f(b) - b * f(a)) / (f(b) - f(a))
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c

    return c


def main():
    xmoc = []
    epsilon = 0.00001
    intervals = {0.9: 1.1,
                 -0.9: -1.1}

    print("\nFunction: something")
    print("Intervals with roots:")
    
    for a, b in intervals.items():
        print("[", a, ",", b, "]")
        xmoc.append(method_of_chords(a, b, epsilon))

    print("\n\tMethod of chords")
    for i in range(len(xmoc)):
        print("x", i + 1, "=", round(x(xmoc[i]), 5), "(", x(xmoc[i]), ")")
        print("y", i + 1, "=", round(xmoc[i], 5), "(", xmoc[i], ")")


if __name__ == "__main__":
    main()
