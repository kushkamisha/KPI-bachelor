from __future__ import (nested_scopes, generators, division, absolute_import,
                        with_statement, print_function, unicode_literals)
import random
import time


class BTree:
    """
    A BTree implementation with search and insert functions. Capable of any
    order t.
    """

    class Node:
        """A simple B-Tree Node."""

        def __init__(self, t):
            self.keys = []
            self.children = []
            self.leaf = True
            # t is the order of the parent B-Tree. Nodes need this value to
            # define max size and splitting.
            self._t = t

        def split(self, parent, payload):
            """Split a node and reassign keys/children."""
            new_node = self.__class__(self._t)

            mid_point = self.size//2
            split_value = self.keys[mid_point]
            parent.add_key(split_value)

            # Add keys and children to appropriate nodes
            new_node.children = self.children[mid_point + 1:]
            self.children = self.children[:mid_point + 1]
            new_node.keys = self.keys[mid_point+1:]
            self.keys = self.keys[:mid_point]

            # If the new_node has children, set it as internal node
            if len(new_node.children) > 0:
                new_node.leaf = False

            parent.children = parent.add_child(new_node)
            if payload < split_value:
                return self
            else:
                return new_node

        @property
        def _is_full(self):
            return self.size == 2 * self._t - 1

        @property
        def size(self):
            return len(self.keys)

        def add_key(self, value):
            """
            Add a key to a node. The node will have room for the key by
            definition.
            """
            self.keys.append(value)
            self.keys.sort()

        def add_child(self, new_node):
            """
            Add a child to a node. This will sort the node's children, allowing
            for children to be ordered even after middle nodes are split.
            returns: an order list of child nodes
            """
            i = len(self.children) - 1
            while i >= 0 and self.children[i].keys[0] > new_node.keys[0]:
                i -= 1
            return self.children[:i + 1] + [new_node] + self.children[i + 1:]

    def __init__(self, t):
        """
        Create the B-tree. t is the order of the tree. Tree has no keys when
        created. This implementation allows duplicate key values, although that
        hasn't been checked strenuously.
        """
        self._t = t
        if self._t <= 1:
            raise ValueError("B-Tree must have a degree of 2 or more.")
        self.root = self.Node(t)

    def insert(self, payload):
        """Insert a new key of value payload into the B-Tree."""
        comparisons = 0
        node = self.root
        # Root is handled explicitly since it requires creating 2 new nodes
        # instead of the usual one.
        if node._is_full:
            comparisons += 1
            new_root = self.Node(self._t)
            new_root.children.append(self.root)
            new_root.leaf = False

            # Node is being set to the node containing the ranges we want for
            # payload insertion.
            node = node.split(new_root, payload)
            self.root = new_root

        while not node.leaf:
            comparisons += 1
            i = node.size - 1
            while i > 0 and payload < node.keys[i]:
                i -= 1
                comparisons += 2
            if payload > node.keys[i]:
                i += 1
                comparisons += 1

            next = node.children[i]
            if next._is_full:
                node = next.split(node, payload)
                comparisons += 1
            else:
                node = next
        # Since we split all full nodes on the way down, we can simply insert
        # the payload in the leaf.
        node.add_key(payload)
        return comparisons

    def search(self, value, node=None):
        """Return True if the B-Tree contains a key that matches the value."""
        if node is None:
            node = self.root
        if value in node.keys:
            return True
        elif node.leaf:
            # If we are in a leaf, there is no more to check.
            return False
        else:
            i = 0
            while i < node.size and value > node.keys[i]:
                i += 1
        return self.search(value, node.children[i])

    def print_order(self):
        """Print an level-order representation."""
        this_level = [self.root]
        while this_level:
            next_level = []
            output = ""
            for node in this_level:
                if node.children:
                    next_level.extend(node.children)
                output += str(node.keys) + " "
            print(output)
            this_level = next_level


def main():
    # t = 1000
    # tree = BTree(t)
    #
    # size = int(input("Enter number of elements: "))
    # my_range = [-500, 500]
    #
    # for _ in range(size):
    #     tree.insert(random.randint(my_range[0], my_range[1]))
    #
    # for _ in range(15):
    #     number = random.randint(my_range[0], my_range[1])
    #     begin = time.time()
    #     found = tree.search(number)
    #     end = time.time()
    #
    #     print(
    #         "Searching for {:4}. Time: {:6f} sec. Found: {}".format(
    #             number, end - begin, found
    #             )
    #         )

    t = 2
    tree = BTree(t)

    lst = [3, 7, 10, 32, 5, 33, 11, 21, 29, 45, 24, 7, 8, 6, 12, 17, 65, 121, 66]


    for _ in lst:
        tree.insert(_)

    tree.print_order()


if __name__ == "__main__":
    main()
