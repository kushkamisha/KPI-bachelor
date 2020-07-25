import my_graph_module as graph

def DFS(start, matr):
    """ Traversal of a graph using DFS method """
    print("DFS")
    start -= 1
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

        print("current vertex ->", parent + 1)
        print("DFS-number ->", counter)
        print("stack -> ", end = "")
        for elem in stack:
            print(elem + 1, end = " ")
        print("\n")
        counter += 1


def BFS(start, matr):
    """ Traversal of a graph using BFS method """
    print("BFS")
    start -= 1
    n = len(matr)
    queue = [start]
    black_list = []
    counter = 1

    while len(queue) != 0:
        parent = queue[0]
        for child in range(n):
            if matr[parent][child] == 1 and not child in black_list:
                queue.append(child)
        black_list.append(parent)
        del queue[0]

        print("current vertex ->", parent + 1)
        print("BFS-number ->", counter)
        print("queue -> ", end = "")
        for elem in queue:
            print(elem + 1, end = " ")
        print("\n")
        counter += 1        


def main():
    matr = graph.output_file_content("input/2.txt")
    start_vert = None
    while not start_vert:
        try:
            start_vert = int(input("Введіть стартову вершину: "))
        except:
            print("Спробуйте ще раз (це мусить бути число)")

    choice = None
    while True:
        choice = input(
        """
        Яким методом обходити граф?
        1 - DFS
        2 - BFS
        """)
        if choice == "1":
            DFS(start_vert, matr)
            break
        elif choice == "2":
            BFS(start_vert, matr)
            break
        else:
            print("В меню відсутній пункт", choice)

    graph.draw_graph(matr)

if __name__ == "__main__":
    main()
