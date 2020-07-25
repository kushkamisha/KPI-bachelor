import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np
import random


def calcWithFormula(_lambda, k):
    num = pd.DataFrame()
    generated = []

    for _ in range(0, 10000):
        x = random.random()
        # generated.append(k / _lambda * (x / _lambda)**(k-1) * np.exp(-(x / _lambda)**k))
        generated.append(_lambda * k**(-_lambda) * x**(_lambda-1) * np.exp(-(x / k)**2))
        # generated.append(_lambda * x**(_lambda-1) * np.exp(-x**_lambda))
    num[_lambda + k] = generated

    return num

    # e_arr = np.random.uniform(0, 0.1, size=(10000))
    # nums = pd.DataFrame()
    # x = k / _lambda * (e_arr / _lambda)**(k-1) * np.exp(-(e_arr / _lambda)**k)
    # nums[str(_lambda + k)] = x

    # return nums


def weibull():
    _lambda = 1
    k = 1
    nums = calcWithFormula(_lambda, k)
    print(nums)

    # print('M:', round(num.mean(), 3))
    # print('D:', round(num.std(), 3))

    # df_unif_stats = pd.DataFrame(num[a + c]
    #                              ).assign(Bin=lambda x: pd.cut(x[a + c], bins=20)
    #                                       ).groupby(['Bin']
    #                                                 ).agg({a + c: ['count']})

    # df_unif_stats.columns = ['count']
    # df_unif_stats = df_unif_stats.reset_index()
    # df_unif_stats['expected'] = 10000 / 20

    # diff = (((df_unif_stats['count'] - df_unif_stats['expected'])
    #          ** 2) / df_unif_stats['expected']).sum()

    # print('a:', num[a + c].min())
    # print('c:', num[a + c].max())
    # print('Diff:', round(diff, 3))
    # print('Critical:', round(stats.chi2.ppf(q=0.95, df=17), 3))

    nums.hist(bins=20)
    plt.show()
