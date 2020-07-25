import my_graph_module as graph

def show(content):
    n = len(content)
    m = len(content[0])
    for i in range(n):
        for j in range(m):
            print("%7.1f" % content[i][j], end = "")
        print()


def find_min(matr):
    """ Find minimum value in the mathrix """
    minn = 9999
    ii = None
    jj = None
    n = len(matr)
    for i in range(n):
        for j in range(n):
            if matr[i][j] < minn:
                minn = matr[i][j]
                ii = i
                jj = j

    return ii, jj



def find_cycle(matr):
    """ """
    counter = 0
    path = []
    N = len(matr)
    INF = 9999
    for i in range(N):
        matr[i][i] = INF

    while N - counter > 2:
        n = len(matr)
        columns = []
        lines = []

        for i in range(n):
            summ = 0
            for j in range(n):
                if matr[i][j] != INF:
                    summ += matr[i][j]
            lines.append(summ / 5)
        for i in range(n):
            summ = 0
            for j in range(n):
                if matr[j][i] != INF:
                    summ += matr[j][i]
            columns.append(summ / 5)
        print(lines)
        print(columns)

        new_matr = [[INF for x in range(n)] for x in range(n)]
        for i in range(n):
            for j in range(n):
                if matr[i][j] != INF:
                    new_matr[i][j] = matr[i][j] - lines[i] - columns[j]

        print("New matrix:")
        print(new_matr)
        ii, jj = find_min(new_matr)
        lst = [ii, jj]
        path.append(lst)
        print(path)

        new_matr = [[INF for x in range(n)] for x in range(n)]
        for i in range(n):
            for j in range(n):
                if i != path[counter][0] and j != path[counter][1]:
                    new_matr[i][j] = matr[i][j]

        matr = new_matr
        matr[path[counter][1]][path[counter][0]] = INF
        show(matr)
        counter += 1

    helpp = []
    for i in range(n):
        for j in range(n):
            if matr[i][j] != INF:
                helpp.append(i)
                break
    path.append(helpp)
    helpp = []
    for i in range(n):
        for j in range(n):
            if matr[j][i] != INF:
                helpp.append(i)
                break
    path.append(helpp)
    print("Path:", path)


def main():
    matr = graph.output_file_content("input/four.txt")
    find_cycle([x[:] for x in matr])
    # graph.draw_graph(matr)


if __name__ == "__main__":
    main()
