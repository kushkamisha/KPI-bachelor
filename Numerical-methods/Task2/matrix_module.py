def input_data(input_matr):
    """ Input matrix and vector b from files """
    # read matrix from file
    file_matr = open(input_matr, "r")
    lst_matr = file_matr.readlines()
    matr = []
    for line in lst_matr:
        line = line.replace("\n", "")
        matr.append(line.split(" "))
    for i in range(len(matr)):
        for j in range(len(matr)):
            matr[i][j] = float(matr[i][j])
    file_matr.close()

    return matr


def show(matr):
    """ Show matrix and vector b """
    # show input matrix
    for i in range(len(matr)):
        for j in range(len(matr)):
            print("%12.5f" % matr[i][j], end = "")
        print()
    print()
