import matplotlib.pyplot as plt
import scipy as sp


class DrawPlot:
    """Can draw any x/y plots."""

    def __init__(
            self,
            xs, ys,
            legends,
            showLine=True,
            title="Different lists comparison",
            xlabel="Time (abstract)",
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
        for x, y, color, legend, marker in zip(
                self.xs, self.ys,
                self.colors,
                self.legends,
                self.dots):
            f2p = sp.polyfit(x, y, 1)
            f2 = sp.poly1d(f2p)

            fx = sp.linspace(0, x[-1], 1000)
            plt.figure(figsize=(12, 8), num=self.figureName)
            plt.plot(
                fx, f2(fx),
                linewidth=int(self.showLine),
                color=color,
                label=legend)

            plt.title(self.title)
            plt.xlabel(self.xlabel)
            plt.ylabel(self.ylabel)

            plt.scatter(x, y, color=color, marker=marker)

        plt.legend(loc='lower right')
        plt.grid(True, linestyle='-', color='0.75')
        plt.show()


def main():
    # arrTimes = [0.00000493, 0.00000461, 0.00000636, 0.00000628, 0.00000660]
    # dllTimes = [0.00000469, 0.00000469, 0.00000612, 0.00000596, 0.00000636]

    arrTimes = [
        100 * 2032,
        1000 * 84036,
        5000 * 2720280,
        10000 * 18255384,
        20000 * 23083124
    ]
    dllTimes = [
        100 * 2060,
        1000 * 83374,
        5000 * 2701506,
        10000 * 18721246,
        20000 * 20013112
    ]

    y = [100, 1000, 5000, 10000, 20000]

    plot = DrawPlot(
            [arrTimes, dllTimes],
            [y, y],
            legends=[
                "2d array",
                "Doubly linked list",
            ]
        )

    plot.show()


if __name__ == "__main__":
    main()
