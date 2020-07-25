def input_data(input_matr, input_b):
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

    # read vector b from file
    file_b = open(input_b, "r")
    lst_b = file_b.readlines()
    b = []
    for elem in lst_b:
        elem = elem.replace("\n", "")
        b.append(elem)
    for i in range(len(b)):
        b[i] = float(b[i])
    file_b.close()

    return matr, b


def show(matr, b, text):
    """ Show matrix and vector b """
    # show input matrix
    print(text)
    for i in range(len(matr)):
        for j in range(len(matr)):
            print("%5.1f" % matr[i][j], end = " ")
        print("|%5.1f" % b[i])