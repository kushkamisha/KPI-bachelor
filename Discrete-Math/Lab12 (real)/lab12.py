INF = 9999
m = [[INF, 5, 11, 9], [10, INF, 8, 7], [7, 14, INF, 8], [12, 6, 15, INF]]
# m = [[INF, 1, 1, 3], [1, INF, 3, 1], [1, 3, INF, 1], [3, 1, 1, INF]]
m_init = [x[:] for x in m]


def reduction(m, n, k, s):
    """ Reduction of the matrix """
    help_lst = []
    for i in range(n):
        if i != s:
            help_lst.append(m[k][i])

    min_row = min(help_lst)

    help_lst = []
    for i in range(n):
        if i != k:
            help_lst.append(m[i][s])

    min_col = min(help_lst)

    return min_row + min_col


n = len(m)
# Show matrix
print()
for i in range(n):
    for j in range(n):
        print("%6d" % m[i][j], end="")
    print()
print()

path = []
flag = True
while flag:
    # Step 2
    di = []
    for i in range(n):
        di.append(min(m[i]))

    # Step 3
    for i in range(n):
        for j in range(n):
            if m[i][j] != INF:
                m[i][j] -= di[i]

    # Step 4
    dj = []
    for i in range(n):
        help_lst = []
        for j in range(n):
            help_lst.append(m[j][i])
        dj.append(min(help_lst))

    # Step 5
    for i in range(n):
        for j in range(n):
            if m[i][j] != INF:
                m[i][j] -= dj[j]

    # Step 6
    max_zero_reduction = []
    for i in range(n):
        for j in range(n):
            if m[i][j] == 0:
                max_zero_reduction.append(reduction(m, n, i, j))

    zero_numb = max_zero_reduction.index(max(max_zero_reduction))
    counter = 0
    for i in range(n):
        for j in range(n):
            if m[i][j] == 0:
                if counter == zero_numb:
                    #print(i + 1, j + 1)
                    path.append([i, j])
                    if j == path[0][0]:
                        flag = False
                    m[j][i] = INF
                    for k in range(n):
                        m[i][k] = INF
                    for k in range(n):
                        m[k][j] = INF
                    break
                counter += 1

# Calc path cost
cost = 0
for road in path:
    cost += m_init[road[0]][road[1]]

# Output result
print("Path: ", end="")
for i in range(len(path)):
    if i == 0:
        print(str(path[i][0] + 1) + "->" + str(path[i][1] + 1), end="")
    else:
        print("->" + str(path[i][1] + 1), end="")

print("\nPath's cost: " + str(cost))
    
