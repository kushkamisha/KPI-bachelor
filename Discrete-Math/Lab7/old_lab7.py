import my_graph_module as graph


def is_lst_in_lst(lst1, lst2):
    """ Check is lst1 contents lst2 """
    n = len(lst2)
    counter = 0
    for elem in lst2:
        if elem in lst1:
            counter += 1
    if counter == n:
        return True
    else:
        return False


def show(lst):
    """ Show two-dimensional array form """
    for k in range(len(lst) - 1):
        n = len(lst) - 1
        for i in range(n):
            for j in range(n):
                if lst[i] != lst[j] and is_lst_in_lst(lst[i], lst[j]):
                    del lst[j]

    print("Кількість компонент зв'язності: ", end = "")
    print(len(lst))
    print("Компоненти зв'язності:")
    number = 1
    for line in lst:
        print(number, "-", end = " ")
        for elem in line:
            print(elem + 1, end = " ")
        number += 1
        print()


def DFS(matr):
    """ Traversal of a graph using DFS method """
    n = len(matr)
    not_used = [0]
    all_black_list = []
    component = []

    while not_used:
        start = not_used[0]
        not_used = []
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

        for elem in black_list:
            if elem not in all_black_list:
                all_black_list.append(elem)
        for i in range(n):
            if i not in all_black_list:
                not_used.append(i)
        component.append(black_list)

    show(component)


def main():
    matr = graph.output_file_content("input/hard.txt") # 1, 3, 4, 5, oriented, hard, cool
    DFS(matr)
        

    graph.draw_graph(matr)


if __name__ == "__main__":
    main()