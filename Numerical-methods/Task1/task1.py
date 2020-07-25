import matrix_module as matrix


def show(mtr):
    """ Print square matrix """
    n = len(mtr)
    m = len(mtr[0])
    for i in range(n):
        for j in range(m):
            print("%6.2f" % mtr[i][j], end=' ')
        print()
    print()


def gaussian_elimination(matr, b, delta):
    """ Gaussian elimination to solve matrix """
    # reduce to triangular form
    n = len(matr)
    for k in range(n - 1):
        for i in range(k, n - 1):
            m = matr[i + 1][k] / matr[k][k]
            for j in range(n):
                matr[i + 1][j] -= m * matr[k][j]
            b[i + 1] -= b[k] * m
        matrix.show(matr, b, "")
    print()

    # calculate delta
    d = 0
    while delta < 1:
        delta *= 10
        d += 1

    # calculate results
    values = []
    n = len(matr)
    for i in range(n - 1, -1, -1):
        s = 0
        for j in range(n - 1 - i):
            s -= matr[i][n - 1 - j] * values[j]
        a = (b[i] + s) / matr[i][i]
        values.append(a)

        # output results
        x_str = "x" + str(i)
        print(x_str, "=", round(a, d))

    # matrix determinant
    det = 1
    for i in range(n):
        det *= matr[i][i]
    print("\nMarix determinant =", round(det, d))


def mtr_plus_unit(mtr):
    """ Append unit matrix at front of mtr """
    n = len(mtr)

    new_matr = [[0 for x in range(2 * n)] for x in range(n)]
    for i in range(n):
        for j in range(2 * n):
            if j < n:
                new_matr[i][j] = mtr[i][j]
            else:
                if i == j - n:# 2*n - j - 1:
                    new_matr[i][j] = 1

    return new_matr


def inverse_matrix(mtr):
    """ Find inverse matrix using Gaussian algorithm """
    # reduce to triangular form
    n = len(mtr)
    nn = len(mtr[0])
    for k in range(n - 1):
        for i in range(k, n - 1):
            m = mtr[i + 1][k] / mtr[k][k]
            for j in range(nn):
                mtr[i + 1][j] -= m * mtr[k][j]

    # reduction of the first part of the matrix to the unit matrix
    for k in range(n - 1):
        div = mtr[n - k - 1][n - k - 1]
        for i in range(2 * n):
            mtr[n - k - 1][i] /= div

        for i in range(n - k - 1):
            elem = mtr[i][n - k - 1]
            for j in range(2 * n):
                mtr[i][j] -= mtr[n - k - 1][j] * elem

    # cut from mtr only inverse matrix
    inv_matr = []
    for i in range(n):
        line = []
        for j in range(n, 2 * n):
            line.append(mtr[i][j])
        inv_matr.append(line)

    print("\nInverse matrix:")
    show(inv_matr)


def main():
    # accuracy of calculation
    delta = 0.001

    # input matirix and b from files
    matr, b = matrix.input_data("input/matrix.txt", "input/b_coef.txt")
    matrix.show(matr, b, "Input matrix")

    # Find the roots of equation
    gaussian_elimination([x[:] for x in matr], [x for x in b], delta)

    # Find extended matrix
    new_matr = mtr_plus_unit(matr)
    show(new_matr)

    # Find inversed matrix
    inverse_matrix(new_matr)


if __name__ == "__main__":
    main()
