import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

def output_file_content():
    """ Displays file content and sets graphs list """
    # get file content
    file = open("input/4.txt", "r")
    lines = file.readlines()
    file.close()

    # display lines
    print("Вміст файлу ingraph.txt:\n")
    for line in lines:
        print(line, end="")
    print("\n")

    # change list for better processing
    graph_matr = []
    for i in lines:
        i = i.replace("\n", "")
        graph_matr.append(i.split())

    return graph_matr


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


def draw_graph(Z):
    """ Draws matrix """
    Z = strmatr_to_intmatr(Z)
    G = nx.from_numpy_matrix(np.array(Z), create_using=nx.MultiDiGraph())
    pos = nx.circular_layout(G)
    nx.draw_circular(G)
    labels = {i : i + 1 for i in G.nodes()}
    nx.draw_networkx_labels(G, pos, labels, font_size=15)
    plt.show()


def is_graph_directed(matr):
    """ Check is graph directed or not """
    n = len(matr)
    number_of_edjes = 0
    not_orient = 0
    for i in range(n):
        for j in range(n):
            if matr[i][j] == "1":
                number_of_edjes += 1
                if matr[j][i] == "1":
                    not_orient += 1

    return (True, False)[number_of_edjes == not_orient]


def degree_of_vertexes(matr, is_directed):
    """ Calc degree of every vertex """
    n = len(matr)
    result = []

    if is_directed:
        for i in range(n):
            counter1  = 0
            counter2 = 0
            for j in range(n):
                if matr[i][j] == "1":
                    counter1 += 1
                elif matr[j][i] == "1":
                    counter2 += 1
            result.append(str(i + 1) + " - " + str(counter1) + ", " + str(counter2))
    else:
        for i in range(n):
            counter = 0
            for j in range(n):
                if matr[i][j] == "1":
                    counter += 1
            result.append(str(i + 1) + " - " + str(counter))

	# is graph regular
    new_res = []
    for i in result:
        new_res.append(i.split(" - "))
	
    edjes_in_1 = new_res[0][1]
    counter = 0
    for i in new_res:
        if edjes_in_1 == i[1]:
            counter += 1
	
    if counter == len(new_res):
        print("Граф однорідний.")
        print("Степінь вершини:", edjes_in_1)
    else:
        print("Граф не є однорідним.")

    show(result)


def hanging_and_isolated_vertexes(matr):
    """ Find hanging and isolated vertexes in the graph """
    handle = []
    isolated = []
    n = len(matr)
    for i in range(n):
        counter = 0
        for j in range(n):
            if matr[i][j] == "1" or matr[j][i] == "1":
                counter += 1
        if counter == 0:
            isolated.append(str(i + 1))
        elif counter == 1:
            handle.append(str(i + 1))
        #print("counter", counter)

	
    to_write = ""
    to_write +="Висячі вершини - "
    for i in handle:
        to_write += i + " "
    to_write += "\nІзольовані вершини - "
    for i in isolated:
        to_write += i + " "

    show(to_write, "string")


def metric_parameters(matr, start_vrt):
    """ Calc diameter, radius, center vertexes and storeys of the graph """
    n = len(matr)
    end_lst = []
    storeys = {}

    for k in range(n):
        queue = []
        black_list = []
        path = {}
        queue.append(k)
        path[k] = 0

        while len(queue) != 0:
            parent = queue[0]
            for child in range(n):
                if matr[parent][child] == "1" and not child in black_list:
                    if not child in path:
                        queue.append(child)
                        path[child] = path[parent] + 1
            black_list.append(parent)
            del queue[0]

        del path[k]
        if k == start_vrt - 1:
            storeys = path

        maximum = 0
        for key in path.values():
            if key > maximum:
                maximum = key
        end_lst.append(maximum)

    minimum = 99999
    maximum = 0
    for i in end_lst:
        if i > maximum:
            maximum = i
        if i < minimum:
            minimum = i

    center = ""
    for i in range(len(end_lst)):
        if end_lst[i] == minimum:
            center += str(i + 1) + " "


    # output results
    out = "Діаметр графу: " + str(maximum) + "\n"
    out += "Радіус графу: " + str(minimum) + "\n"
    out += "Центральні вершини графу: " +  str(center) + "\n"
    out += "Яруси графу:" + "\n"

    # number of storeys for start_vrt
    max_depth = 0
    for i in storeys.values():
        if i > max_depth:
            max_depth = i

    # storeys of the graph
    for i in range(1, max_depth + 1):
        out += str(i) + " - " + " "#print(i, "-", end = " ")
        for key, value in storeys.items():
            if value == i:
                out += str(key + 1) + " "#print(key, end = " ")
        out += "\n"

    show(out, "string")


def show(result, mode = "list"):
    """ Ask where output result and output result """
    def out_on_screen(content):
        """ Displays content on screen """
        if mode == "list":
            for i in content:
                print(i)
        elif mode == "string":
            print(content)

    def out_in_file(content):
        """ Save content in the file """
        file = open("output.txt", "w")
        if mode == "list":
            for i in content:
                file.write(i + "\n")
        elif mode == "string":
            file.write(content)

        print("\nФайл успішно записано...")
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


def main():
    # input graph
    graph_matr = output_file_content()

    is_directed = is_graph_directed(graph_matr)

    choice = None
    while True:
        choice = input("""
    	Що робити?
    	1 - визначити степінь вершин графу
    	2 - визначити всі висячі та ізольовані вершини графу
    	3 - визначити метричні характеристики графу
    	""")
        if choice == "1":
            degree_of_vertexes(graph_matr, is_directed)
            break
        elif choice == "2":
            hanging_and_isolated_vertexes(graph_matr)
            break
        elif choice == "3":
            start_vertex = int(input("Для якої вершини шукати яруси?\n"))
            metric_parameters(graph_matr, start_vertex)
            break
        else:
            print("В меню відсутній пункт", choice)

    draw_graph(graph_matr)


if __name__ == "__main__":
    main()
