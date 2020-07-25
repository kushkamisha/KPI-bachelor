import networkx as nx
import matplotlib.pyplot as plt


def removeDuplicateEdjes(lst):
	"""Removes one of duplicate edjes such as 1-3, 3-1"""
	new_list = []
	for key, val in lst:
		if [key, val] and [val, key] not in new_list:
			new_list.append([key, val])

	return new_list

#takes input from the file and creates a undirected graph
def CreateGraph():
	G = nx.Graph()
	# f = open('inputs/input.txt')
	# n = int(f.readline())

	lst = [[0, 4], [1, 2], [1, 3], [2, 1], [2, 4], [3, 1], [3, 4], [4, 0], [4, 2], [4, 3]]
	lst = removeDuplicateEdjes(lst)

	for row in lst:
		# graph_edge_list = f.readline().split()
		# print(graph_edge_list)
		G.add_edge(row[0], row[1])
	return G

#draws the graph and displays the weights on the edges
def DrawGraph(G,col_val):
	pos = nx.spring_layout(G)
	# values = [col_val.get(node, 'pink') for node in G.nodes()]
	values = ['red', 'blue', 'yellow', 'purple', 'red', 'blue', 'yellow']
	# with_labels=true is to show the node number in the output graph
	nx.draw(G, pos, with_labels = True, node_color = values, edge_color = 'black' ,width = 1, alpha = 0.7)




#main function
if __name__ == "__main__":
	G = CreateGraph()
	# col_val = welsh_powell(G)
	col_val = {}
	for i in range(7):
		col_val[i] = 1

	DrawGraph(G,col_val)
	plt.show()
