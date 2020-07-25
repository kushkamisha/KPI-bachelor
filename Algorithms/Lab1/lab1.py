import random
import time
import pickle
import sys
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
import math


class QuickSort:
    """QuickSort algorithm with Hoare partition scheme."""

    def __init__(self, lst):
        """Init list and auxiliary variables."""
        self.lst = lst
        self.comparisons = 0
        self.swaps = 0
        self.maxRecursionLevel = 0

    def sort(self):
        """Sort list with the quicksort method."""
        self.quickSort(self.lst, 0, len(self.lst)-1, self.maxRecursionLevel)

    def showResult(self):
        """Show sorted list and additional sorting information."""
        # print("List after sort:", self.lst)
        print("Number of comparisons:", self.comparisons)
        print("Number of swaps:", self.swaps)
        print("Max recursion lever:", self.maxRecursionLevel)

    def quickSort(self, lst, first, last, recursionLevel):
        """Main quicksort function."""

        # Calculate recursion level.
        if (recursionLevel > self.maxRecursionLevel):
            self.maxRecursionLevel = recursionLevel

        if first < last:
            self.comparisons += 1

            splitpoint = self.partition(self.lst, first, last)

            self.quickSort(self.lst, first, splitpoint-1, recursionLevel+1)
            self.quickSort(self.lst, splitpoint+1, last, recursionLevel+1)

    def partition(self, lst, first, last):
        """Additional quicksort function to divide list on two parts."""

        pivotvalue = lst[first]

        leftmark = first + 1
        rightmark = last

        done = False
        while not done:

            while leftmark <= rightmark and lst[leftmark] <= pivotvalue:
                leftmark += 1

            while lst[rightmark] >= pivotvalue and rightmark >= leftmark:
                rightmark -= 1

            if rightmark < leftmark:
                done = True
            else:
                lst[leftmark], lst[rightmark] = lst[rightmark], lst[leftmark]
                self.swaps += 1

        lst[first], lst[rightmark] = lst[rightmark], lst[first]
        self.swaps += 1

        return rightmark

    def __exit__(self):
        """Exempts memory after using the class."""
        print("Destructor")
        del self.lst[:]
        del self.comparisons
        del self.swaps
        del self.maxRecursionLevel


class EvaluateAlgorithm:
    """Evaluate the quicksort algorithm for different lists."""

    def __init__(self):
        self.lengths = [10, 100, 1000, 2000, 5000, 10000, 20000]
        self.folders = ['10', '100', '1000', '2000', '5000', '10000', '20000']
        self.files = ['ordered', 'backordered', 'random']

    def saveToFile(self):
        """Save different lists to files."""
        for lng, folder in zip(self.lengths, self.folders):
            ordered = [x for x in range(1, lng+1)]
            backordered = [x for x in range(lng, 0, -1)]
            rand = [random.randint(1, lng) for x in range(lng)]

            with open('data/' + folder + '/' + self.files[0], 'wb') as file:
                pickle.dump(ordered, file)
            with open('data/' + folder + '/' + self.files[1], 'wb') as file:
                pickle.dump(backordered, file)
            with open('data/' + folder + '/' + self.files[2], 'wb') as file:
                pickle.dump(rand, file)

    def evaluate(self):
        """
        Evaluate the time of sorting with the quicksort algorithm for different
        lists.
        """
        sys.setrecursionlimit(40000)

        evaluation = list()
        for folder in self.folders[5:]:
            line = []
            print("Folder:", folder)
            with open('data/' + folder + '/' + self.files[0], 'rb') as file:
                ordered = pickle.load(file)
                quicksort = QuickSort(ordered)

                start = time.time()
                quicksort.sort()
                end = time.time()

                quicksort.showResult()

                del quicksort
                line.append(end - start)
                print("Ordered:", line[0])
                print("\n\n")

            with open('data/' + folder + '/' + self.files[1], 'rb') as file:
                backordered = pickle.load(file)
                quicksort = QuickSort(backordered)

                start = time.time()
                quicksort.sort()
                end = time.time()

                quicksort.showResult()

                del quicksort
                line.append(end - start)
                print("Backordered:", line[1])
                print("\n\n")

            with open('data/' + folder + '/' + self.files[2], 'rb') as file:
                rand = pickle.load(file)
                quicksort = QuickSort(rand)

                start = time.time()
                quicksort.sort()
                end = time.time()

                quicksort.showResult()

                del quicksort
                line.append(end - start)
                print("Random:", line[2])
                print("\n\n")

            evaluation.append(line)

        return evaluation

    def bestTime(self, n):
        """Best algorithm's working time."""
        return n * math.log(n)

    def worstTime(self, n):
        """The worst algorithm's working time."""
        return n*n

    def showPlots(self):
        """Shows 3 plots for 3 types of arrays. Plot is time/size."""

        # times = [
        #     [6.198883056640625e-05, 5.412101745605469e-05,
        #         3.886222839355469e-05],
        #     [0.0013110637664794922, 0.0012891292572021484,
        #         0.00041794776916503906],
        #     [0.11106300354003906, 0.10880279541015625, 0.0057849884033203125],
        #     [0.41941189765930176, 0.42520689964294434, 0.015279054641723633],
        #     [2.740694046020508, 2.76031494140625, 0.03850197792053223],
        #     [10.79902696609497, 11.202094078063965, 0.0696408748626709],
        #     [37.34802293777466, 36.93501591682434, 0.1409311294555664]
        # ]
        # numElements = [10, 100, 1000, 2000, 5000, 10000, 20000]
        orderedTimes = [9 * 10, 99 * 100, 999 * 1000, 1999 * 2000, 4999 * 5000, 9999 * 10000, 19999 * 20000]
        backorderedTimes = [9 * 10, 99 * 100, 999 * 1000, 1999 * 2000, 4999 * 5000, 9999 * 10000, 19999 * 20000]
        randTimes = [4 * 10, 14 * 100, 22 * 1000, 24 * 2000, 30 * 5000, 30 * 10000, 34 * 20000]

        # for ordered, backordered, rand in times:
        #     orderedTimes.append(ordered)
        #     backorderedTimes.append(backordered)
        #     randTimes.append(rand)

        lng = len(orderedTimes)

        best = [self.bestTime(x) for x in range(1, 20000)]
        worst = [self.worstTime(x) for x in range(1, 20000)]
        y = [x for x in range(1, 20000)]

        plot = DrawPlot(
                [orderedTimes, backorderedTimes, randTimes, best, worst],
                [self.lengths, self.lengths, self.lengths, y, y],
                legends=[
                    "Ordered lists",
                    "Backordered lists",
                    "Random data lists",
                    "O(n*log(n))",
                    "O(n^2)",
                ]
            )

        # asymptoticEvaluation = DrawPlot(
        #         [best, worst],
        #         [y, y],
        #         legends=[
        #             "O(n*log(n))",
        #             "O(n^2)",
        #         ],
        #         showLine=False
        #     )

        plot.show()
        # asymptoticEvaluation.show()


class DrawPlot:
    """Can draw any x/y plots."""

    def __init__(
            self,
            xs, ys,
            legends,
            showLine=True,
            title="Different lists comparison",
            xlabel="Time (sec)",
            ylabel="Length (elements)",
            figureName="Quicksort evaluation"):
        """Set all necessary parameters."""
        self.xs = xs
        self.ys = ys
        self.legends = legends
        self.showLine = showLine
        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel
        self.figureName = figureName
        self.colors = ['b', 'm', 'y', 'c', 'g', 'r', 'k']
        self.dots = ['x', 'o', 'v', '*', '+', '.', ',']

    def show(self):
        """Show the plot."""
        for x, y, color, legend, marker in zip(self.xs, self.ys, self.colors, self.legends, self.dots):
            f2p = sp.polyfit(x, y, 2)
            f2 = sp.poly1d(f2p)

            fx = sp.linspace(0, x[-1], 1000)
            plt.figure(figsize=(12, 8), num=self.figureName)
            plt.plot(fx, f2(fx), linewidth=int(self.showLine), color=color, label=legend)

            plt.title(self.title)
            plt.xlabel(self.xlabel)
            plt.ylabel(self.ylabel)

            plt.scatter(x, y, color=color, marker=marker)

        plt.legend(loc='lower right')
        plt.grid(True, linestyle='-', color='0.75')
        plt.show()


def main():

    # Ask user about list parameters.
    # n = int(input("Enter number of elements in the list\n> "))
    # minValue = int(input("Enter min possible value in the list\n> "))
    # maxValue = int(input("Enter max possible value in the list\n> "))

    # print("n =", n)
    # print("max =", maxValue)
    # print("min =", minValue)

    # lst = [random.randint(minValue, maxValue) for x in range(n)]
    # lst = [x for x in range(1, 101)]
    # print("List before sort:", lst)

    # quickSortClass = QuickSort(lst)

    # start = time.time()
    # quickSortClass.sort()
    # end = time.time()

    # quickSortClass.showResult()

    # print("Working time: %f sec" % (end - start))

    # Test the algorithm
    evaluate = EvaluateAlgorithm()
    # evaluation = evaluate.evaluate()
    # print(evaluation)
    evaluate.showPlots()
    # evaluate.saveToFile()


if __name__ == '__main__':
    main()
