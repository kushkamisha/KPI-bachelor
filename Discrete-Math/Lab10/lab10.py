import my_graph_module as graph


def check_for_euler_path(m):
    """
    Try to find Euler path in the graph
    and return true if founded and false if not
    """
    n = len(m)
    m_copy = [x[:] for x in m]
    for i in range(n):
        for j in range(n):
            if m[i][j] != 0:
                m_copy[j][i] = m[i][j]
    
    odd_verteces = []
    odd_verteces2 = []
    for vertex in range(n):
        sum1 = sum2 = 0
        for block in m_copy[vertex]:
            sum1 += block
        for block in m[vertex]:
            sum2 += block
        if sum1 % 2 != 0:
            odd_verteces.append(vertex)
        if sum2 % 2 != 0:
            odd_verteces2.append(vertex)

    if odd_verteces == []:
        return []
    else:
        return odd_verteces2


def is_bridge(m, a, b):        
    m_copy = [x[:] for x in m]
    m_copy[a][b] = 0
    m_copy[b][a] = 0
    black_a = sorted(graph.DFS(a, m_copy))
    black_b = sorted(graph.DFS(b, m_copy))
    if black_a == black_b:
        return False
    else:
        return True


def find_euler_path(m, start):
    """Find Euler path in the graph"""
    n = len(m)
    stack = [start]
    path = [start]

    matr = [x[:] for x in m]
    for i in range(n):
        for j in range(n):
            if matr[i][j] != 0:
                matr[j][i] = matr[i][j]

    while stack:
        vertex = stack[0]
        del stack[0]
        childrens = []
        for i in range(n):
            if m[vertex][i] != 0:
                childrens.append(i)
        
        for i in range(len(childrens)):
            if i != len(childrens) - 1:
                if not is_bridge(matr, vertex, childrens[i]):
                    stack.append(childrens[i])
                    path.append(childrens[i])
                    m[vertex][childrens[i]] = 0
                    matr[vertex][childrens[i]] = 0
                    matr[childrens[i]][vertex] = 0
                    break
            else:
                stack.append(childrens[i])
                path.append(childrens[i])
                m[vertex][childrens[i]] = 0
                matr[vertex][childrens[i]] = 0
                matr[childrens[i]][vertex] = 0
                break

    print("Path: ", end = "")
    for i in range(len(path)):
        if i != len(path) - 1:
            print(path[i] + 1, "-> ", end = "")
        else:
            print(path[i] + 1)


def main():
    matr = graph.output_file_content("input/4.txt") # 4, 1
    odd_verteces = check_for_euler_path(matr)

    # power of every vertex in the graph
    verteces_numb = []
    for line in matr:
        sum = 0
        for elem in line:
            if elem != 0:
                sum += 1
        verteces_numb.append(sum)
    
    print("Degree of the every vertex:")
    for i in range(len(verteces_numb)):
        print(i + 1, "-", verteces_numb[i])
    
    if odd_verteces == []:
        print("There is no Euler cycle in the graph")
    else:
        vertex = odd_verteces[0]
        find_euler_path([x[:] for x in matr], vertex)
    graph.draw_graph(matr)


if __name__ == "__main__":
    main()
