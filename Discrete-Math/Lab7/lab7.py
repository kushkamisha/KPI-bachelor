import my_graph_module as graph


def DFS(start, matr):
    """ Traversal of a graph using DFS method, returns list of not reached vertexes """
    n = len(matr)
    stack = [start]
    black_list = []
    counter = 1

    while len(stack) != 0:
        parent = stack[len(stack) - 1]
        del stack[len(stack) - 1]
        black_list.append(parent)
        for child in range(n):
            if not child in black_list and matr[parent][child] == 1:
                if not child in stack:
                    stack.append(child)
        counter += 1
    
    return black_list


def find_components(matr):
    """  """
    n = len(matr)
    answer = []
    for i in range(n):
        component = []
        childrens = DFS(i, matr)
        childrens.sort()
        for child in childrens:
            lst = DFS(child, matr)
            lst.sort()
            if lst == childrens:
                component.append(child)
        if not component in answer:
            answer.append(component)
    
    i = 1
    for line in answer:
        print(i, "-", end = " ")
        for elem in line:
            print(elem + 1, end = " ")
        print()
        i += 1


def main():
    matr = graph.output_file_content("input/wiki.txt") # 1, 3, 4, 5, oriented, hard, cool, wiki
    find_components(matr)

    graph.draw_graph(matr)


if __name__ == "__main__":
    main()
