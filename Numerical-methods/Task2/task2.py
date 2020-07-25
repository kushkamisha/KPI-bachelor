import matrix_module as matrix
import math

def matrix_multiply(m1, m2):
    """ Multiply two square matrixes """
    n = len(m1)
    res_m = [[0 for x in range(n)] for x in range(n)]
    
    for i in range(n):
        for j in range(n):
            cell = 0
            for k in range(n):
                cell += m1 [i][k] * m2 [k][j]
            res_m [i][j] = cell
    return res_m


def to_frobenius_form(matr):
    """ Change matrix to Frobenius normal form """
    n = len(matr)
    
    for k in range(1, n):
        start_A = [x[:] for x in matr]
        print("A:")
        matrix.show(matr)
        
        # create B
        B = [[ 0 for x in range(n)] for x in range(n)]
        for i in range(n):
            for j in range(n):
                if i == j:
                    B [i][j] = 1
        for i in range(n):
            if i == n - 1 - k:
                B [n - 1 - k][i] = 1 / matr [n - k][n - 1 - k]
            else:
                B [n - 1 - k][i] = -matr [n - k][i] / matr [n - k][n - 1 - k]
        print("M:")
        matrix.show(B)

        # A * B
        matr = matrix_multiply(matr, B)
        print("A * M:")
        matrix.show(matr)

        B_1 = [[ 0 for x in range(n)] for x in range(n)]
        for i in range(n):
            for j in range(n):
                if i == j:
                    B_1 [i][j] = 1
        for i in range(n):
            B_1 [n - 1 - k][i] = start_A [n - k][i]
        print("M^-1:")
        matrix.show(B_1)

        # B^-1 * A * B
        print("M^-1 * A * M:")
        mult_m = matrix_multiply(B_1, matr)
        matrix.show(mult_m)

        matr = [x[:] for x in mult_m]
        print("---------------------------------------------------------")

    out = ""
    for i in range(n):
        out += "x^" + str(n - i) + " "
        out += str(round(-matr[0][i], 5))
        if i != n - 1:
            out += " + "
    print(out)

def main():
    matr = matrix.input_data("input/input_matr.txt")
    to_frobenius_form(matr)


if __name__ == "__main__":
    main()