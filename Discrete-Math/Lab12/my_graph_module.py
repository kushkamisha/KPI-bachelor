# moduls for draw_graph()
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

def output_file_content(f_name):
    """ Displays file content and sets graphs matrix """
    # get file content
    file = open(f_name, "r")
    lines = file.readlines()
    file.close()

    # change list for better processing
    graph_matr = []
    for i in lines:
        i = i.replace("\n", "")
        graph_matr.append(i.split())

    # # display matrix
    # print("\nThe contents of the file " + f_name + ":\n")
    # graph_matr = strmatr_to_intmatr(graph_matr)
    # n = len(graph_matr)
    # m = len(graph_matr[0])
    # for i in range(n):
    # 	for j in range(m):
    # 		print("%4d" % graph_matr[i][j], end = " ")
    # 	print()
    # print("\n")

    return graph_matr


def draw_graph(Z):
    """ Draws graph from matrix """
    print("\n\n")
    Z = strmatr_to_intmatr(Z)
    G = nx.from_numpy_matrix(np.array(Z), create_using=nx.MultiDiGraph())
    pos = nx.circular_layout(G)
    nx.draw_circular(G)
    labels = {i : i + 1 for i in G.nodes()}
    nx.draw_networkx_labels(G, pos, labels, font_size=15)
    plt.show()


def hanging_and_isolated_vertexes(matr):
    """ Find hanging and isolated vertexes in the graph """
    handle = []
    isolated = []
    n = len(matr)
    for i in range(n):
        counter = 0
        for j in range(n):
            if matr[i][j] == 1 or matr[j][i] == 1:
                counter += 1
        if counter == 0:
            isolated.append(i + 1)
        elif counter == 1:
            handle.append(i + 1)
	
    return handle, isolated


def is_graph_directed(matr):
    """ Check is graph directed or not """
    n = len(matr)
    number_of_edjes = 0
    not_orient = 0
    for i in range(n):
        for j in range(n):
            if matr[i][j] == 1:
                number_of_edjes += 1
                if matr[j][i] == 1:
                    not_orient += 1

    return (True, False)[number_of_edjes == not_orient]


def distance_to_vertixes(matr):
    """ Calc distances to other vertixes for every vertex"""
    n = len(matr)
    distances = []

    for k in range(n):
        queue = []
        black_list = []
        path = {}
        queue.append(k)
        path[k] = 0

        while len(queue) != 0:
            parent = queue[0]
            for child in range(n):
                if matr[parent][child] == 1 and not child in black_list:
                    if not child in path:
                        queue.append(child)
                        path[child] = path[parent] + 1
            black_list.append(parent)
            del queue[0]

        del path[k]
        distances.append(path)

    return distances


def show(result, mode = "list"):
    """
    Ask where output result and output result
    mode:
    'list' - when you must display some structure (formated output)
    'matr' - if input data is nxm matrix
    'string' - just displays string
    """
    def out_on_screen(content):
        """ Displays content on screen """
        if mode == "list":
            for i in content:
                print(i)
        elif mode == "string":
            print(content)
        elif mode == "matr":
            n = len(content)
            m = len(content[0])
            for i in range(n):
                for j in range(m):
                    print("%3i " % content[i][j], end = "")
                print()

    def out_in_file(content):
        """ Save content in the file """
        file = open("output.txt", "w")
        if mode == "list":
            for i in content:
                file.write(i + "\n")
        elif mode == "string":
            file.write(content)

        print("\nФайл output.txt успішно записано...")
        file.close()

    choice = None
    while True:
        choice = input("""
    	Як відображати результати?
    	1 - показати на екрані
    	2 - зберегти до файлу
    	3 - показати на екрані і зберегти до файлу
    	""")
        if choice == "1":
            out_on_screen(result)
            break
        elif choice == "2":
            out_in_file(result)
            break
        elif choice == "3":
            out_on_screen(result)
            out_in_file(result)
            break
        else:
            print("В меню відсутній пункт", choice)


def DFS(start, matr):
    """ Traversal of a graph using DFS method """
    # print("DFS")
    n = len(matr)
    stack = [start]
    black_list = []

    while len(stack) != 0:
        parent = stack[len(stack) - 1]
        del stack[len(stack) - 1]
        black_list.append(parent)
        for child in range(n):
            if not child in black_list and matr[parent][child] == 1:
                if not child in stack:
                    stack.append(child)

        print("current vertex ->", parent + 1)
        print("stack -> ", end = "")
        for elem in stack:
            print(elem + 1, end = " ")
        print("\n")

    return black_list


def BFS(start, matr):
    """ Traversal of a graph using BFS method """
    print("BFS")
    start -= 1
    n = len(matr)
    queue = [start]
    black_list = []
    # counter = 1

    while len(queue) != 0:
        parent = queue[0]
        for child in range(n):
            if matr[parent][child] == 1 and not child in black_list:
                queue.append(child)
        black_list.append(parent)
        del queue[0]

        print("current vertex ->", parent + 1)
        # print("BFS-number ->", counter)
        print("queue -> ", end = "")
        for elem in queue:
            print(elem + 1, end = " ")
        print("\n")
        # counter += 1
    print(black_list)
        

                ####################################
                ## Don't uses in result module    ##
                ## Just help work other functions ##
#########################################################################

def strmatr_to_intmatr(Z):
    """ Try to convert all elements in matrix to int type """
    n = len(Z)
    new_Z = []
    for i in range(n):
        help_Z = []
        for j in range(n):
            help_Z.append(int(Z[i][j]))
        new_Z.append(help_Z)

    return new_Z
