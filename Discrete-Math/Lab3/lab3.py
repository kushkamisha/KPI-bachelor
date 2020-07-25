import my_graph_module as graph
import numpy as np
from copy import deepcopy

def distance_and_reach_matr(matr):
    """ Creates matrix of distance and matrix of reach from input matrix """
    # distance matrix
    distance = graph.distance_to_vertixes(matr)
    n = len(matr)
    if graph.is_graph_directed(matr):
        matr_distance = [[-1 for x in range(n)] for y in range(n)]
        for i in range(n):
            matr_distance[i][i] = 0
    else:
        matr_distance = [[0 for x in range(n)] for y in range(n)]

    current_vertex = 0
    for line in distance:
        for vertex, deep in line.items():
            matr_distance[current_vertex][vertex] = deep
        current_vertex += 1

    # reach matrix
    reach_matr = [[0 for x in range(n)] for y in range(n)]
    for i in range(n):
        for j in range(n):
            reach_matr[i][j] = matr_distance[i][j]

    if graph.is_graph_directed(matr):
        for i in range(n):
            for j in range(n):
                if reach_matr[i][j] == -1:
                    reach_matr[i][j] = 0
                else:
                    reach_matr[i][j] = 1
    else:
        for i in range(n):
            for j in range(n):
                if not reach_matr[i][j] == 0:
                    reach_matr[i][j] = 1
            reach_matr[i][i] = 1

    return matr_distance, reach_matr


def find_cycles(matr):
    """ Find cycles in graph and if finded show one cycle on the screen """
    # simplify graph for find cycles
    hanging =[9]
    while hanging != []:
        hanging, isolated = graph.hanging_and_isolated_vertexes(matr)
        n = len(matr)
        for vert in reversed(hanging):
            for i in range(n):
                matr[vert - 1][i] = 0
                matr[i][vert - 1] = 0

    # DFS to find cycles
    have_cycles = False
    for k in range(n):
        stack = [k]
        black_list = []
        while len(stack) != 0:
            parent = stack[len(stack) - 1]
            del stack[len(stack) - 1]
            black_list.append(parent)
            for child in range(n):
                if not child in black_list and matr[parent][child] == 1:
                    if not child in stack:
                        stack.append(child)
                    else:
                        if not have_cycles:
                            print("Граф має прості цикли: ", end = "")
                            cycle = black_list[:]
                            cycle.append(child)
                            #print(cycle)
                            for elem in cycle:
                                print(elem + 1, end = " - ")
                            print(cycle[0] + 1)
                            have_cycles = True
                            break
    if not have_cycles:
        print("Граф не має простих циклів")


def is_connected(matr):
    """ Check is graph connected with all other vertexes or not """
    # only for not directed graph
    n = len(matr)

    for i in range(n):
        for j in range(n):
            if matr[i][j] == 1:
                matr[j][i] = 1

    matr_distance, reach_matr = distance_and_reach_matr(matr)

    counter = 0
    for i in range(n):
        for j in range(n):
            if reach_matr[i][j] == 1:
                counter += 1
    if counter == n * n:
        return True
    else:
        return False


def type_of_connect(m, reach_m):
    n = len(reach_m)
    
    if graph.is_graph_directed(m):
        print("Тип графу: ", end = "")
        if not is_connected([x[:] for x in m]):
            print("незв'язний")
        else:

            # is strongly connected
            counter = 0
            for i in range(n):
                for j in range(n):
                    if reach_m[i][j] == 1:
                        counter += 1
            if counter == n * n:
                print("сильнозв'язний")
            else:
                # is one-sided coupled matrix
                trans_m = matrix_transposition([x[:] for x in reach_m])
                added_m = [[0 for x in range(n)] for x in range(n)]
                for i in range(n):
                    for j in range(n):
                        added_m[i][j] = reach_m[i][j] + trans_m[i][j]
                #print(added_m)
                counter = 0
                for i in range(n):
                    for j in range(n):
                        if added_m[i][j] == 0:
                            counter += 1
                if counter == 0:
                    print("однозв'язний")
                else:
                    # is weakly connected
                    print("слабкозв'язний")

        # сильнозв'язний
        # однозв'язний
        # слабкозв'язний
        # незв'язний
    else:
        print("Граф не є орієнтовним, тому не можна визначити характеристик орієнтованого графа.")


def matrix_transposition(matr):
    """ Returns transposition matrix for given one """
    n = len(matr)
    new_matr = [[0 for x in range(n)] for x in range(n)]
    for i in range(n):
        for j in range(n):
            new_matr[i][j] = matr[j][i]

    return new_matr


def main():
    matr = graph.output_file_content("input/lab5.txt")
    choice = None
    while True:
        choice = input("""
            Що робити?
            1 - визначити матриці відстаней та досяжності графу
            2 - визначити наявність простих циклів у графі
            3 - визначити тип зв'язності графу
            """)
        if choice == "1":
            matr_distance, reach_matr = distance_and_reach_matr(matr)

            print("\nМатриця відстаней", end = "")
            graph.show(matr_distance, "matr")

            print("\nМатриця досяжності", end = "")
            graph.show(reach_matr, "matr")
            break
        elif choice == "2":
            find_cycles([x[:] for x in matr])
            break
        elif choice == "3":
            matr_distance, reach_matr = distance_and_reach_matr(matr)
            type_of_connect(matr, reach_matr)
            break
        else:
            print("В меню відсутній пункт", choice)

    graph.draw_graph(matr)


if __name__ == "__main__":
    main()
