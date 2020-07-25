import random
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np


def checkFunction(x,_lambda):
    return 1 - np.e ** (-_lambda * x)


def calcWithFormula(_lambda):
    e_arr = np.random.uniform(size=(10000))
    nums = pd.DataFrame()
    x = (-1/_lambda) * np.log(e_arr)
    nums[str(_lambda)] = x

    return nums


def gen1(_lambda):
    nums = calcWithFormula(_lambda)

    print('M:', round(nums.mean(), 3))
    print('D:', round(nums.std() ** 2, 3))

    nums_ranges = pd.DataFrame(nums[str(_lambda)]
        ).assign(Bin=lambda x: pd.cut(x[str(_lambda)], bins=20)
        ).groupby(['Bin']).agg({str(_lambda): ['count']})

    nums_ranges.columns = ['count']
    nums_ranges = nums_ranges.reset_index()
    nums_ranges['expected'] = nums_ranges['Bin'].apply(
        lambda x: 
            checkFunction(x.right, _lambda) -
            checkFunction(x.left, _lambda)
        ).astype(float)*10000

    diff = ((nums_ranges['count'] - nums_ranges['expected']) ** 2 /
             nums_ranges['expected']
           ).sum()

    print('Lambda:', _lambda)
    print('Diff:', round(diff, 3))
    print('Critical:', round(stats.chi2.ppf(q=0.95, df=18), 3))

    nums.hist(bins=20)
    plt.show()
