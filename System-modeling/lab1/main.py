import sys
from generators.gen1 import gen1
from generators.gen2 import gen2
from generators.gen3 import gen3
from generators.weibull import weibull


def preprocess_cli_args(length=4):
    """
    Add undefined elements to the cli arguments up to make it a constant length,
    parse existing elements to the int type
    """
    for i in range(1, len(sys.argv)):
        sys.argv[i] = int(sys.argv[i])
        if (sys.argv[i] <= 0 or sys.argv[i] > length):
            sys.argv[i] = 1
    for _ in range(len(sys.argv), length):
        sys.argv.append(None)


def main():
    lambdas = [0.5, 0.3, 2]
    a2, sigma = [0, 1, 2], [2, 5, 3]
    a3, c = [5**13, 5**12, 5**11], [2**31, 2**30, 2** 35]

    preprocess_cli_args()

    if (sys.argv[1] is None):
        sys.argv[1] = 1
        sys.argv[2] = 1

    print(sys.argv)

    if (sys.argv[1] == 1):
        gen1(lambdas[sys.argv[2]-1])

    elif (sys.argv[1] == 2):
        if (sys.argv[2] is None):
            sys.argv[2] = 1
        if (sys.argv[3] is None):
            sys.argv[3] = 1
        gen2(a2[sys.argv[2]-1], sigma[sys.argv[3]-1])

    elif (sys.argv[1] == 3):
        if (sys.argv[2] is None):
            sys.argv[2] = 1
        if (sys.argv[3] is None):
            sys.argv[3] = 1
        gen3(a3[sys.argv[2]-1], c[sys.argv[3]-1])
    
    # gen1(0.5)
    # gen2(0, 1)
    # gen3(5**13, 2**31)
    # weibull()

if __name__ == "__main__":
    main()
