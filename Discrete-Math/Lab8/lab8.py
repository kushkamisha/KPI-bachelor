import my_graph_module as gr
import networkx as nx

INF = 1000 * 1000 * 1000

def min(a, b):
    return a if a < b else b


def min_in_matrix(matr):
    """ Find min element in the square matrix """
    n = len(matr)
    minimum = INF
    for i in range(n):
        for j in range(n):
            if matr [i][j] < minimum:
                minimum = matr [i][j]

    return minimum


def LeviticusAlgorithm(g, s, f):
    print("""
             ---------------------
            | Leviticus algorithm |
             ---------------------
          """)
    n = len(g)
    d = [INF for i in range(n)]
    d[s] = 0
    p = [int(-1) for i in range(n)]
    m0 = [] # vertexes with calculated distance
    m1 = [s] # vertexes with calculation in progress
    m2 = [] # vertexes with not calculated distance

    for i in range(n):
        if i != s:
            m2.append(i)

    while m1:
        # choose vertex
        v = m1[0]
        del m1[0]

        # push vertex in m0
        m0.append(v)

        for i in range(n):
            if g [v][i] != 0:
                t = i # child vertex
                l = g [v][i] # weight of child vertex
                if t in m2:
                    m1.append(t)
                    m2.remove(t)
                    d[t] = d[v] + l
                    #if p[t] != s:
                    p[t] = v
                elif t in m1:
                    d[t] = min(d[t], d[v] + l)
                    #if p[t] != s:
                    p[t] = v
                elif t in m0 and d[t] > d[v] + l:
                    d[t] = d[v] + l
                    m1.insert(0, t)
                    m0.remove(t)
                    #if p[t] != s:
                    p[t] = v
    print("The shortest path between", s + 1, "and", f + 1, "is", d[f])
    line = "The path from " + str(s + 1) + " to " + str(f + 1) + " is "

    lst = [f]
    elem = p[f]
    while elem != s:
        lst.insert(0, elem)
        elem = p[elem]
    lst.insert(0, elem)

    k = len(lst)
    for i in range(k):
        if i != k - 1:
            line += str(lst[i] + 1) + " - "
            #print(lst[i] + 1, end = " - ")
        else:
            line += str(lst[i] + 1) + "\n\n"
            #print(lst[i] + 1, end = "\n\n")
    print(line)
    return line


def DanzigAlgorithm(graph, start, finish):
    print("""
             ------------------
            | Danzig algorithm |
             ------------------
          """)
    nodes = graph.keys()

    distance = {}

    for n in nodes:

        distance[n] = {}

        for k in nodes:

            distance[n][k] = graph[n][k]

    for k in nodes:

        for i in nodes:

            for j in nodes:

                if distance[i][k] + distance[k][j] < distance[i][j]:

                    distance[i][j] = distance[i][k]+distance[k][j]

    n = len(distance)
    for i in range(n):
        print(i + 1, "-", end = " ")
        for j in range(n):
            if distance[i][j] == INF:
                print("inf ", end = "")
            else:
                print(distance[i][j], end = " ")
        print()

    

def main():
    matr = gr.output_file_content("input/wiki.txt") # hard
    start = int(input("Input start vertex (from 1 to n): ")) - 1 # start vertex
    finish = int(input("Input finish vertex (from 1 to n): ")) - 1 # finish vertex
    line = LeviticusAlgorithm(matr, start, finish)
    
    # transform to dict form
    n = len(matr)
    graph = {}
    for i in range(n):
        dct = {}
        for j in range(n):
            if i != j and matr[i][j] == 0:
                dct[j] = INF
            else:
                dct[j] = matr[i][j]
        graph[i] = dct
    
    DanzigAlgorithm(graph, start, finish)
    print("\n" + line)

    gr.draw_graph(matr)


if __name__ == "__main__":
    main()