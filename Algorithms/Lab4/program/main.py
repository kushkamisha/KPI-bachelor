import math


class Dijkstra:
    """Graph traversal using Dijkstra's algorithm"""
    def __init__(self, startNode, filename='matrix.txt'):
        """Init necessary params"""
        # Get adjacency matrix from file
        self.matrix = self.__getMatrixFromFile(filename)

        # Number of nodes in the graph
        self.n = len(self.matrix)

        # Start node to find path from it to all other nodes
        self.startNode = startNode

        # Mark all nodes as unvisited
        self.unvisited = [True for _ in range(self.n)]

        # Mark distances to all the nodes except first one as infinity
        self.distances = [math.inf for _ in range(self.n)]
        self.distances[self.startNode] = 0

    def showAdjacencyMatrix(self):
        """Display adjacency matrix on the screen"""
        print('\n======================')
        print('== Adjacency matrix ==')
        print('======================')
        for row in self.matrix:
            for val in row:
                print('{:3}'.format(val), end='')
            print()
        print()

    def process(self):
        """Traverse the graph using Dijkstra's algorithm"""
        q = [i for i in range(self.n)]  # vertexes
        previous = [[] for _ in range(self.n)]

        while q != []:
            # Node with the least distance
            minVertex = 0
            minValue = math.inf
            for vertex in q:
                if self.distances[vertex] < minValue:
                    minVertex = vertex
                    minValue = self.distances[vertex]
            u = minVertex
            q.remove(u)

            for v in self.__getNeighbors(u):
                alt = self.distances[u] + self.matrix[u][v]

                # A shortest path to v has been found
                if alt < self.distances[v]:
                    self.distances[v] = alt
                    previous[v] = u

        return self.distances, previous

    def __getNeighbors(self, node):
        """Get list of neighbors for the current node"""
        lst = []
        for i in range(self.n):
            if self.matrix[node][i] != 0:
                lst.append(i)

        return lst

    def __getMatrixFromFile(self, filename):
        """Read adjacency matrix from file"""
        with open(filename, 'r') as f:
            lines = f.readlines()
            matrix = []
            matrixInt = []
            for line in lines:
                matrix.append(line.replace('\n', '').split(' '))

            # Convert string values to int
            for row in matrix:
                matrixInt.append([int(val) for val in row])

            return matrixInt


class Astar:
    """Graph traversal using A* algorithm"""
    def __init__(self, start, filename='A-star-matrix.txt',
                 heuristicFilename='A-star-heuristic.txt'):
        """Init necessary params"""
        # Get adjacency matrix from file
        self.matrix = self.__getMatrixFromFile(filename)

        self.heuristicFilename = heuristicFilename

        # Number of nodes in the graph
        self.n = len(self.matrix)

        # Start node to find path from it to all other nodes
        self.start = start

        self.visited = []
        self.previousNodes = [[] for _ in range(self.n)]
        self.totalDistances = [math.inf for _ in range(self.n)]
        self.shortestDistancesFromStart = [math.inf for _ in range(self.n)]
        self.shortestDistancesFromStart[start] = 0

    def showAdjacencyMatrix(self):
        """Display adjacency matrix on the screen"""
        print('\n======================')
        print('== Adjacency matrix ==')
        print('======================')
        for row in self.matrix:
            for val in row:
                print('{:4}'.format(val), end='')
            print()
        print()

    def process(self):
        """Traverse the graph using A* algorithm"""
        current = self.start
        self.totalDistances[current] = \
            self.shortestDistancesFromStart[current] + \
            self.heuristic(current)

        # Loop
        while True:
            unvisitedNeighbors = self.__getUnvisitedNeighbors(current)

            for neighbor in unvisitedNeighbors:
                if (self.shortestDistancesFromStart[current] +
                        self.matrix[current][neighbor] <
                        self.shortestDistancesFromStart[neighbor]):
                    self.shortestDistancesFromStart[neighbor] = \
                        self.shortestDistancesFromStart[current] + \
                        self.matrix[current][neighbor]
                    self.totalDistances[neighbor] = \
                        self.shortestDistancesFromStart[neighbor] + \
                        self.heuristic(neighbor)
                    self.previousNodes[neighbor] = current

            self.visited.append(current)

            # Find unvisited node with the shortest distance from start
            smallestUnvisitedNode = math.inf
            smallestDistance = math.inf
            for node in range(self.n):
                if self.totalDistances[node] < smallestDistance and \
                   node not in self.visited:
                    smallestUnvisitedNode = node
                    smallestDistance = self.totalDistances[node]

            # All nodes are visited
            if len(self.visited) == self.n:
                break

            current = smallestUnvisitedNode

        return [self.shortestDistancesFromStart, self.previousNodes]

    def heuristic(self, node):
        # Only to Sault Ste Marie node
        h = self.__getMatrixFromFile(self.heuristicFilename)

        return h[0][node]

    def __getUnvisitedNeighbors(self, node):
        """Get list of neighbors for the current node"""
        lst = []
        for i in range(self.n):
            if self.matrix[node][i] != 0 and (i not in self.visited):
                lst.append(i)

        return lst

    def __getMatrixFromFile(self, filename):
        """Read adjacency matrix from file"""
        with open(filename, 'r') as f:
            lines = f.readlines()
            matrix = []
            matrixInt = []
            for line in lines:
                matrix.append(line.replace('\n', '').split(' '))

            # Convert string values to int
            for row in matrix:
                matrixInt.append([int(val) for val in row])

            return matrixInt


def formatPathways(start, pathways, cities):
    """Get pathways, formated as a string"""
    order = []
    n = len(pathways)

    # Get nodes order
    for node in range(n):
        if pathways[node] == []:
            order.append([])
            continue

        temp = [node]
        current = pathways[node]

        while current != start:
            temp.insert(0, current)
            current = pathways[current]
        temp.insert(0, start)

        order.append(temp)

    # Get path strings from orders
    iterator = 0
    output = []
    for path in order:
        current = path[:]
        if path == []:
            output.append("<empty>")
        else:
            output.append(" -> ".join([cities[val] for val in current]))
        iterator += 1

    return output


def main():
    start = 11  # Sault Ste Marie
    cities = ['Boston', 'Chicago', 'Denver', 'Duluth', 'Helena', 'Kansas City',
              'Montreal', 'New York', 'Omaha', 'Pittsburg', 'Saint Louis',
              'Sault Ste Marie', 'Toronto', 'Washington', 'Winnipeg']

    dijkstra = Dijkstra(start, filename='USA-matrix.txt')
    astar = Astar(start, filename='USA-matrix.txt',
                  heuristicFilename='USA-heuristic.txt')

    d_costs, d_pathways = dijkstra.process()
    a_costs, a_pathways = astar.process()

    d_pathwaysStr = formatPathways(start, d_pathways, cities)
    a_pathwaysStr = formatPathways(start, a_pathways, cities)

    # Beuatiful output
    # Dijkstra's algorithm
    print(
        """\n
        ==========================
        == Dijkstra's algorithm ==
        ==========================
        """
        )
    iteration = 0
    for cost, path in zip(d_costs, d_pathwaysStr):
        print("From " + cities[start] + " to " + cities[iteration] + ":")
        print("\tCost: " + str(cost) + 'km')
        print("\tPath:", path)
        iteration += 1

    # A* algorithm
    print(
        """\n
        ==========================
        ====== A* algorithm ======
        ==========================
        """
        )
    iteration = 0
    for cost, path in zip(d_costs, d_pathwaysStr):
        print("From " + cities[start] + " to " + cities[iteration] + ":")
        print("\tCost: " + str(cost) + 'km')
        print("\tPath:", path)
        iteration += 1


if __name__ == "__main__":
    main()
