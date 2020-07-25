import my_graph_module as graph

def topological_sorting(matr):
    """ Topological sorting using DFS method """
    n = len(matr)
    black_list = []
    
    for start in range(n):
        if start in black_list:
            continue
        stack = [start]
        
        while len(stack) != 0:
            parent = stack[len(stack) - 1]

            childrens = 0
            for child in range(n - 1, -1, -1):
                if not child in black_list and matr[parent][child] == 1:
                    if not child in stack:
                        stack.append(child)
                        childrens += 1
            if not childrens:
                del stack[len(stack) - 1]
                black_list.append(parent)

    print("Топологічне сортування (номер обходу / вершина):\n")
    i = 1
    for elem in reversed(black_list):
        print(i, "-", elem + 1)
        i += 1

def main():
    matr = graph.output_file_content("input/1.txt")
    topological_sorting(matr)
    graph.draw_graph(matr)

if __name__ == "__main__":
    main()
