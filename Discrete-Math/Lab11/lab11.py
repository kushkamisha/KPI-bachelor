import my_graph_module as graph


def output(lst):
    """ Output results """
    n = len(lst)
    print("Hamiltonian route: ", end = "")
    for i in lst:
        print(i + 1, end = " ")
    print("\nHamiltonian cycle: ", end = "")
    for i in lst:
        print(i + 1, end = " ")
    print(lst[0] + 1, end = "\n\n")


def FindPath(matr):
    """ Find Gamilton path in the graph """
    n = len(matr)
    start = 0
    black_list = []
    stack = [start, start]
    verteces = []
    prev_parent = -1
    for i in range(n):
        verteces.append(i)

    while stack != []:
        no_childs = True
        parent = stack[0]
        del stack[0]
        black_list.append(parent)
        # print("\nParent:", parent)

        for i in range(n):
            if matr[parent][i] != 0 and i != prev_parent:
                if i != prev_parent:
                    no_childs = False
                # print("i =", i)
                if i in black_list:
                    # print("i in black list")
                    # path found
                    if i == start and black_list == verteces:
                        # print("Path found:", black_list)
                        break
                    # reverse
                    if no_childs:
                        deleted = []
                        # print("No childs")
                        if black_list == verteces:
                            output(black_list)
                            break
                        while no_childs and stack != []:
                            vertex = black_list[len(black_list) - 1]
                            deleted.append(vertex)
                            del black_list[len(black_list) - 1]
                            for i in range(n):
                                if matr[vertex][i] != 0 and not i in black_list and not i in deleted:
                                    black_list.append(vertex)
                                    no_childs = False
                                    break
                else:
                    if not i in stack:
                        stack.insert(0, i)

        # print("Black list:", black_list)
        # print("Stack:", stack)

        # if vertex doesn't have childs -> reverse
        if no_childs:
            deleted = []
            # print("No childs")
            counter = 0
            for i in range(n):
                if i in black_list:
                    counter += 1
            # print("Counter:", counter)
            if counter == n:
                output(black_list)
                break
            while no_childs and stack != []:
                vertex = black_list[len(black_list) - 1]
                deleted.append(vertex)
                del black_list[len(black_list) - 1]
                for i in range(n):
                    if matr[vertex][i] != 0 and not i in black_list and not i in deleted:
                        black_list.append(vertex)
                        no_childs = False
                        break


            # print("Black list:", black_list)
            # print("Stack:", stack)
        prev_parent = parent

    if stack == []:
        print("Sorry, but the graph does not contain a Hamiltonian cycle and route.")


def main():
    matr = graph.output_file_content("input/8.txt")
    FindPath(matr)
    graph.draw_graph(matr)


if __name__ == "__main__":
    main()
