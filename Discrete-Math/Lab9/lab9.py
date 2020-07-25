import my_graph_module as graph

INF = 1000 * 1000 * 1000
ZERO = 1 / INF


def bellman_ford(mtr):
    """ 
    Find the shortiest path from start vertex
    to others using Bellman-Ford algorithm 
    """
    n = len(mtr)
    distance = [[INF for x in range(n)] for x in range(n)]
    for k in range(n):
        distance[k][k] = 0

        # find distances
        for i in range(1, n):
            for u in range(n):
                for v in range(n):
                    if mtr[u][v] != 0:
                        if distance[k][u] + mtr[u][v] < distance[k][v]:
                            distance[k][v] = distance[k][u] + mtr[u][v]

        # check is graph contains a negative-weight cicle
        for u in range(n):
            for v in range(n):
                if mtr[u][v] != 0:
                    if distance[k][u] + mtr[u][v] < distance[k][v]:
                        return False

    return distance

def dijkstra(start, mtr):
    """
    Find the shortest path from start vertex
    to others using Dijkstra algorithm 
    """
    n = len(mtr)
    distance = [INF for x in range(n)]
    distance[start] = 0
    predecessor = [None for x in range(n)]
    unvisited = []
    for v in range(n):
        unvisited.append(v)
    
    while unvisited:
        min = INF + 1
        min_vertex = None
        for u in range(n):
            if u in unvisited and distance[u] < min:
                min = distance[u]
                min_vertex = u
        unvisited.remove(min_vertex)

        for v in range(n):
            if mtr[min_vertex][v] != 0:
                alt = distance[min_vertex] + mtr[min_vertex][v]
                if alt < distance[v]:
                    distance[v] = alt
                    predecessor[v] = min_vertex

    return distance, predecessor


def johnson(start, finish, mtr):
    """
    Find the shortest path from start vertex
    to finish using Johnson's algorithm 
    """
    n = len(mtr)
    etalon_mtr = [x[:] for x in mtr]
    lst = []
    for i in range(n):
        mtr[i].append(0)
        lst.append(ZERO)
    lst.append(0)
    mtr.append(lst)
    # print(mtr)
    
    distance = bellman_ford(mtr)
    if distance == False:
        print("Graph contains a negative-weight cicle")
    else:
        h = distance[n]
        for i in range(n + 1):
            h[i] = round(h[i])
        # print("h:", h)

        for u in range(n):
            for v in range(n):
                if mtr[u][v] != 0:
                    mtr[u][v] = mtr[u][v] + h[u] - h[v]
                    if mtr[u][v] == 0:
                        mtr[u][v] = ZERO
        
        for i in range(n):
            del mtr[i][n]
        del mtr[n]
        # print(mtr)

        # calculate the shortest path
        dst, predecessor = dijkstra(start, mtr)
        if predecessor[finish] == None:
            print("\nThere is no path between", start + 1, "and", finish + 1, "verteces.")
        else:
            print("\nPath between", start + 1, "and", finish + 1, "verteces is ", end = "")
            predecessor[start] = 0
            path = reconstruct_path(predecessor, start, finish)
            mm = len(path)
            for index in range(mm):
                if index != mm - 1:
                    print(path[index] + 1, "-", end = " ")
                else:
                    print(path[index] + 1)

            # calculate the shortest distance in primary graph
            lst = [finish]
            elem = predecessor[finish]
            while elem != start:
                lst.insert(0, elem)
                elem = predecessor[elem]
            lst.insert(0, elem)

            distance = 0
            for i in range(len(lst) - 1):
                distance += etalon_mtr[lst[i]][lst[i + 1]]
            print("The distance is:", distance)


def reconstruct_path(predecessor, start, finish):
    """ Helps a_star function find path """
    lst = [finish]
    elem = predecessor[finish]
    while elem != start:
        lst.insert(0, elem)
        elem = predecessor[elem]
    lst.insert(0, elem)
    return lst


def a_star(start, finish, mtr): 
    """
    Find the shortest path from start vertex
    to finish using A* algorithm
    """
    # find heuristic path from all verteces to finish vertex
    flag = False
    n = len(mtr)
    heuristic = []
    for i in range(n):
        heuristic.append(-INF)

    # algorithm
    closed_set = []
    open_set = [start]
    came_from = [0 for x in range(n)]
    g_score = [INF for x in range(n)]
    g_score[start] = 0
    f_score = [INF for x in range(n)]
    f_score[start] = heuristic[start]

    while open_set:
        current = open_set[0]
        for i in range(n):
            if i in open_set and f_score[i] < f_score[current]:
                current = i
        if current == finish:
            # print(came_from)
            path = reconstruct_path(came_from, start, current)
            print("\nPath between", start + 1, "and", finish + 1, "verteces is ", end = "")
            mm = len(path)
            for index in range(mm):
                if index != mm - 1:
                    print(path[index] + 1, "-", end = " ")
                else:
                    print(path[index] + 1)

            distance = 0
            for i in range(mm - 1):
                distance += mtr[path[i]][path[i + 1]]
            print("The distance is", distance)

            flag = True
            break
        open_set.remove(current)
        closed_set.append(current)
        for neighbor in range(n):
            if mtr[current][neighbor] != 0:
                if neighbor in closed_set:
                    continue

                tentative_gscore = g_score[current] + mtr[current][neighbor]
                if not (neighbor in open_set):
                    open_set.append(neighbor)
                elif tentative_gscore >= g_score[neighbor]:
                    continue


                came_from[neighbor] = current
                g_score[neighbor] = tentative_gscore
                f_score[neighbor] = g_score[neighbor] + heuristic[neighbor]

    if not flag:
        print("\nThere is no path between", start + 1, "and", finish + 1, "verteces.")


def main():
    """ The main function """
    matr = graph.output_file_content("input/negative_circle.txt") # super_minus, oriented3, negative_circle
    n = len(matr)

    # input start and finish verteces
    start = -1
    while start < 1 or start > n:
        try:
            start = int(input("Input start vertex: ")) 
        except:
            start = -1
            print("Incorrect input, try again...")

    finish = -1
    while finish < 1 or finish > n:
        try:
            finish = int(input("Input finish vertex: "))
        except:
            finish = -1
            print("Incorrect input, try again...")

    start -= 1
    finish -= 1

    # choose algorithm
    choice = None
    while True:
        choice = input(
        """
        Choose algorithm:
        1 - Johnson's
        2 - A*
        """)
        if choice == "1":
            johnson(start, finish, [x[:] for x in matr])
            break
        elif choice == "2":
            a_star(start, finish, [x[:] for x in matr])
            break
        else:
            print("In the menu there is no choice", choice)

    # graph.draw_graph(matr)


if __name__ == "__main__":
    main()
