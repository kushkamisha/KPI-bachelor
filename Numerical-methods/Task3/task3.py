def f(x, n):
    """Return value of a function"""
    if n == 0:
        return (x + 1) ** 3 - x
    elif n == 1:
        return x**3 + 0.2 * x**2 + 0.5 * x + 0.8
    else:
        return 0


def f_derivative(x, n):
    """Return value of derivative of a function"""
    if n == 0:
        return 3 * (x + 1) ** 2 - 1
    elif n == 1:
        return 3 * x**2 + 0.4 * x + 0.5
    else:
        return 0


def bisection_method(a, b, epsilon, n):
    """
    Find the roots of equation
    using bisection method
    """
    c = 9999
    while abs(f(c, n)) >= epsilon and abs(b - a) >= epsilon:
        c = (a + b) / 2
        if f(a, n) * f(c, n) < 0:
            b = c
        else:
            a = c
    return c


def method_of_chords(a, b, epsilon, n):
    """
    Find the roots of equation
    using method of chords
    """
    c = 9999
    while abs(f(c, n)) >= epsilon and abs(b - a) >= epsilon:
        c = (a * f(b, n) - b * f(a, n)) / (f(b, n) - f(a, n))
        if f(a, n) * f(c, n) < 0:
            b = c
        else:
            a = c

    return c


def newtons_method(x0, epsilon, n):
    """
    Find the roots of equation
    using Newton's method
    """
    x = x0 - f(x0, n) / f_derivative(x0, n)
    x_prev = x0
    while abs(f(x, n)) >= epsilon:
        x_prev = x
        x = x_prev - f(x_prev, n) / f_derivative(x_prev, n)

    return x


def main():
    epsilon = 0.001
    
    # (x+1)^3 - x = 0
    xbm = []
    xmoc = []
    xnm = []
    intervals = {-2.5: -2}
    print("\nFunction: (x+1)^3 - x = 0")
    print("Intervals with roots:")
    
    for a, b in intervals.items():
        print("[", a, ",", b, "]")
        xbm.append(bisection_method(a, b, epsilon, 0))
        xmoc.append(method_of_chords(a, b, epsilon, 0))
        xnm.append(newtons_method(a, epsilon, 0))

    print("\n\tBisection method")
    for i in range(len(xbm)):
        print("x", i + 1, "=", round(xbm[i], 3), "(", xbm[i], ")")

    print("\n\tMethod of chords")
    for i in range(len(xmoc)):
        print("x", i + 1, "=", round(xmoc[i], 3), "(", xmoc[i], ")")

    print("\n\tNewton's method")
    for i in range(len(xnm)):
        print("x", i + 1, "=", round(xnm[i], 3), "(", xnm[i], ")")


    # x^3 + 0.2 * x^2 + 0.5 * x + 0.8 = 0
    xbm = []
    xmoc = []
    xnm = []
    intervals = {-1: -0.7}
    print("\nFunction: x^3 + 0.2 * x^2 + 0.5 * x + 0.8 = 0")
    print("Intervals with roots:")
    
    for a, b in intervals.items():
        print("[", a, ",", b, "]")
        xbm.append(bisection_method(a, b, epsilon, 1))
        xmoc.append(method_of_chords(a, b, epsilon, 1))
        xnm.append(newtons_method(a, epsilon, 1))

    print("\n\tBisection method")
    for i in range(len(xbm)):
        print("x", i + 1, "=", round(xbm[i], 3), "(", xbm[i], ")")

    print("\n\tMethod of chords")
    for i in range(len(xmoc)):
        print("x", i + 1, "=", round(xmoc[i], 3), "(", xmoc[i], ")")

    print("\n\tNewton's method")
    for i in range(len(xnm)):
        print("x", i + 1, "=", round(xnm[i], 3), "(", xnm[i], ")")


if __name__ == "__main__":
    main()
