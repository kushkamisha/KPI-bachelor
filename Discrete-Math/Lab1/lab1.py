def output_file_content():
    """ Displays file content and sets graphs list """
    # get file content
    file = open("/Users/Romanusherenko/Documents/Misha/Python/Дискретка/Lab1/input_not_direct.txt", "r")
    lines = file.readlines()
    file.close()

    #import os, sys
    #print(os.path.realpath(os.path.dirname(sys.argv[0])))

    # display lines
    print("Вміст файлу ingraph.txt:\n")
    for line in lines:
        print(line, end="")
    print("\n")

    # change list for better processing
    graph_list = []
    for i in lines:
        i = i.replace("\n", "")
        graph_list.append(i.split(" "))

    return graph_list


def directed_graph(graph_list):
    """ Check is graph directed or not """
    counter = 0
    for i in range(len(graph_list)):
        a = graph_list[i][0]
        b = graph_list[i][1]
        rev_line = [b, a]
        for line in graph_list:
            if line == rev_line:
                counter += 1
                
    return (True, False)[counter == len(graph_list)]


def ask_matr_questions(n, graph_list, is_directed):
    """ What matrix create and how it displays """
    # ask what matrix create
    choice = None
    while True:
        choice = input("""
        Яку матрицю вивести?
        1 - інцидентності
        2 - суміжності
        """)
        if choice == "1":
            matrix = incidence_matrix(n, graph_list, is_directed)
            break
        elif choice == "2":
            matrix = adjacency_matrix(n, graph_list)
            nn = n
            break
        else:
            print("В меню немає пункту", choice)

    # ask show matrix on screen or save in the file
    choice = None
    while True:
        choice = input("""
        Куди виводити матрицю?
        1 - на екран
        2 - в файл
        3 - і на екран, і в файл
        """)
        if choice == "1":
            out_on_screen(matrix)
            break
        elif choice == "2":
            out_in_file(matrix)
            break
        elif choice == "3":
            out_on_screen(matrix)
            out_in_file(matrix)
            break
        else:
            print("В меню немає пункту", choice)


def number_of_vertexes(lst):
    """ Calculates number of bertexes in the graph """
    maximum = 0
    local_max = 0
    for i in range(len(lst)):
        local_max = int(lst[i][0] > lst[i][1] and lst[i][0] or lst[i][1])
        maximum = maximum > local_max and maximum or local_max

    return maximum
        

def incidence_matrix(n, graph_list, is_directed):
    """ Creates incidence matrix """
    # check is graph directed
    if not is_directed:

        # new list without extra elements
        new_graph = []
        for i in range(len(graph_list)):
            a = graph_list[i][0]
            b = graph_list[i][1]
            rev_line = [b, a]
            is_alone = True
            for j in range(i, len(graph_list)):
                if graph_list[j] == rev_line:
                    is_alone = False
            if is_alone:
                new_graph.append(rev_line)
        graph_list = new_graph

    # create blank matrix n x nn
    nn = len(graph_list)
    matrix = [[0 for row in range(0,nn)] for col in range(0,n)]

    # fill matrix
    counter = 0
    for i in graph_list:
        if is_directed:
            matrix[int(i[0]) - 1][counter] = -1
            matrix[int(i[1]) - 1][counter] = 1
            counter += 1
        else:
            matrix[int(i[0]) - 1][counter] = 1
            matrix[int(i[1]) - 1][counter] = 1
            counter += 1
    
    return matrix


def adjacency_matrix(n, graph_list):
    """ Creates adjacency matrix """
    # create blank matrix n x n
    matrix = [[0 for row in range(0,n)] for col in range(0,n)]

    # fill matrix
    for k in range(len(graph_list)):
        i = int(graph_list[k][0]) - 1
        j = int(graph_list[k][1]) - 1
        matrix[i][j] = 1

    return matrix


def out_on_screen(m):
    """ Displays matrix on screen """
    n = len(m)
    nn = len(m[0])
    print("\n")
    for i in range(n):
        for j in range(nn):
            print("%4i" % m[i][j], end = "")
        print("\n")


def out_in_file(m):
    """ Saves matrix in file """
    # create list from matrix to write in file
    n = len(m)
    nn = len(m[0])
    m_list = []
    for i in range(n):
        help_str = ""
        for j in range(nn):
            #help_str += str(m[i][j]) + "   "
            help_str += str("%4i" % m[i][j])
        help_str += "\n"
        m_list.append(help_str)

    # write list in file
    file = open("/Users/Romanusherenko/Documents/Misha/Python/Дискретка/Lab1/output.txt", "w")
    file.writelines(m_list)
    file.close()
    print("Записано в файл output.txt")


def main():
    # show what is in the file and get graphs list
    graph_list = output_file_content()
    is_directed = directed_graph(graph_list)
    print("Is graph directed?", is_directed)

    # number of vertexes
    n = number_of_vertexes(graph_list)

    # asks questions about matrix
    ask_matr_questions(n, graph_list, is_directed)
    

if __name__ == "__main__":
    main()
