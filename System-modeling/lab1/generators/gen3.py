import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np


def calcWithFormula(a, c):
    num = pd.DataFrame()
    z = 1
    generated = []
    for _ in range(10000):
        x = z / c
        z = (a*z) % c
        generated.append(x)
    num[a + c] = generated

    return num


def gen3(a, c):
    num = calcWithFormula(a, c)
    # print(num)

    print('M:', round(num.mean(), 3))
    print('D:', round(num.std(), 3))

    df_unif_stats = pd.DataFrame(num[a + c]
        ).assign(Bin=lambda x: pd.cut(x[a + c], bins=20)
        ).groupby(['Bin']
        ).agg({a + c: ['count']})

    df_unif_stats.columns = ['count']
    df_unif_stats = df_unif_stats.reset_index()
    df_unif_stats['expected'] = 10000 / 20

    diff = (((df_unif_stats['count'] - df_unif_stats['expected'])
             ** 2) / df_unif_stats['expected']).sum()

    print('a:', num[a + c].min())
    print('c:', num[a + c].max())
    print('Diff:', round(diff, 3))

    num.hist(bins=20)
    plt.show()
