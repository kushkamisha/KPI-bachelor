import random
import math
import time


class HashTable():
    """Hash table implementation."""
    def __init__(self, size, structType='dict'):
        """Init all necessary parameters."""
        self.size = size
        self.structType = structType
        self.hashTable = dict()
        self.lst = [[x, None] for x in range(self.size)]

        self.initHashTable()
        self.currentSize = 0
        self.comparisons = 0

        self.A = (5**(1/2) - 1) / 2
        self.M = 2**64

    def initHashTable(self):
        """Init blank hash table."""
        for i in range(self.size):
            self.hashTable[i] = None

    def getKey(self, value):
        """Get key using multiplying algorithm."""
        return math.floor(self.M * (value * self.A % 1))

    def getKey2(self, value):
        """Get key using divide algorithm."""
        return value % self.size

    def add(self, value):
        """Add new element to the hash table."""
        if (self.currentSize >= self.size):
            print("Out of free space in the hash table.")
            return

        self.comparisons += 1

        i = 0
        x = self.getKey(value)
        y = self.getKey2(value)

        key = x

        while True:
            # key = (x + i*y) % self.size
            key = key % self.size

            if (self.structType == 'dict'):
                if (self.hashTable[key] is None):
                    self.hashTable[key] = value
                    self.currentSize += 1
                    break
                else:
                    i += 1
                    key += 1
            else:
                if (self.lst[key][1] is None):
                    self.lst[key][1] = value
                    self.currentSize += 1
                    break
                else:
                    i += 1
                    key += 1

            self.comparisons += 2

    def search(self, key):
        """Get element by key from the hash table."""
        if (key >= 0 and key < self.size):
            if (self.structType == 'dict'):
                return self.hashTable[key]
            else:
                return self.lst[key][1]

        return None

    def show(self):
        """Show all non-empty elements in the hash table."""
        counter = 0

        if (self.structType == 'dict'):
            for (key, value) in self.hashTable.items():
                if value is not None:
                    print(key, value)
                    counter += 1
        else:
            for key, value in self.lst:
                if value is not None:
                    print(key, value)
                    counter += 1

        print("\nSize:", counter, "\n")

    def getNumOfComparisons(self):
        """Get number of comparisons in the algorithm."""
        return self.comparisons


def main():
    values = [random.randint(0, 100) for x in range(100)]

    tableSize = 101
    structType = 'arr'

    hashTable = HashTable(tableSize, structType)

    for value in values:
        hashTable.add(value)

    hashTable.show()

    start = time.time()

    print("Search(0):", hashTable.search(0))
    print("Search(1):", hashTable.search(1))
    print("Search(2):", hashTable.search(2))

    end = time.time()

    print("Search time (of one element): {:.8f} sec".format((end - start) / 3))

    print("\nNumber of comparisons:", hashTable.getNumOfComparisons())

    if (structType == 'dict'):
        print('\nStructure type: doubly linked list')
    else:
        print('\nStructure type: 2 dimensional array')


if __name__ == "__main__":
    main()
