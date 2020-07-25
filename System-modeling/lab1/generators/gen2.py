import random
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np


def checkFunction(a, sigma, x):
    return stats.norm.cdf((x - a) / sigma) - 0.5


def calcWithFormula(a, sigma):
    e_arr = np.random.uniform(size=(10000, 12))
    nums = pd.DataFrame()
    mus = np.sum(e_arr, axis=1) - 6
    x = sigma * mus + a
    nums[str(a + sigma)] = x

    return nums


def gen2(a, sigma):
    nums = calcWithFormula(a, sigma)
    print(nums)

    print('M:', round(nums.mean(), 3))
    print('D:', round(nums.std() ** 2, 3))

    nums_ranges = pd.DataFrame(nums[str(a + sigma)]
        ).assign(Bin=lambda x: pd.cut(x[str(a + sigma)], bins=20)
        ).groupby(['Bin']
        ).agg({str(a + sigma): ['count']})

    nums_ranges.columns = ['count']
    nums_ranges = nums_ranges.reset_index()
    nums_ranges['expected'] = nums_ranges['Bin'].apply(
        lambda x: 
            checkFunction(a, sigma, x.right) -
            checkFunction(a, sigma, x.left)
        ).astype(float)*10000
    diff = ((nums_ranges['count'] - nums_ranges['expected'])** 2 /
             nums_ranges['expected']
           ).sum()

    print('a:', a)
    print('sigma:', sigma)
    print('Diff:', round(diff, 3))

    nums.hist(bins=20)
    plt.show()
