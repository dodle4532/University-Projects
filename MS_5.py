import numpy as np
import pandas as pd
from openpyxl import Workbook
import matplotlib.pyplot as plt
from scipy.stats import norm
from scipy.stats import chi2
import math

def create_table(sample):
    reshaped_sample = sample.reshape(20, 10)
    df = pd.DataFrame(reshaped_sample)
    df.to_excel("table.xlsx", index=False)

def create_sorted_table(sample):
    sorted_sample = np.sort(sample)
    reshaped_sample = sorted_sample.reshape(20, 10)
    df = pd.DataFrame(reshaped_sample)
    df.to_excel("sorted_table.xlsx", index=False)


def plot_empirical_cdf(sample, a, b):
    n = len(sample)
    cumulative_probabilities = np.arange(1, n + 1) / n
    x_uniform = np.linspace(a - (b-a)/10, b + (b-a)/10, 1000) 
    y_uniform = np.zeros_like(x_uniform)
    y_uniform[(x_uniform >= a) & (x_uniform <= b)] = (x_uniform[(x_uniform >= a) & (x_uniform <= b)] - a) / (b - a)
    y_uniform[x_uniform > b] = 1
    cdf = pd.DataFrame({'x': x_uniform, 'cdf': y_uniform})
    plt.figure(figsize=(10, 6))
    plt.plot(sample, cumulative_probabilities, color='blue', linewidth=2, label='График эмперической функции распределения выборки') 
    plt.plot(cdf['x'], cdf['cdf'], linestyle='--', color = 'red', label='График функции распределения равномерного закона')
    plt.xlabel("Значение")
    plt.ylabel("Эмпирическая функция распределения")
    plt.title("Эмпирическая функция распределения")
    plt.grid(True)
    plt.xlim(left=0, right=sample.max() * 1.1) 
    plt.legend()
    plt.show()

def create_table1(sample, a, b):
    cols = []
    for j in range(sample.size):
        cols.append(max(abs((j+1)/sample.size - (sample[j]-a) / (b-a)), abs(j/sample.size - (sample[j]-a) / (b-a))))
    max_arg = np.argmax(cols)
    y = sample[max_arg]
    d = cols[max_arg]

    table = pd.DataFrame([{
        'a': a,
        'b': b,
        'N': sample.size,
        'D_N': d,
        'D_N*sqrt(N)': d*math.sqrt(sample.size),
        'y*': y,
        'F(y*)': (y - a) / (b-a),
        'F_N(y*)': (max_arg+1)/sample.size,
        'F_N(y*-0)': max_arg/sample.size
    }])
    table.to_excel("table5_1.xlsx", index=False)
    return table


sample = np.array([
3.56729,1.91532,1.75496,0.60988,4.92115,1.31827,3.21486,1.76448,4.18726,0.72311,
2.23232,1.75774,4.15388,1.48528,2.53803,1.95748,5.30158,0.80641,4.70308,1.96381,
5.52906,3.21974,5.16957,1.59253,5.15092,4.80997,2.90238,5.38334,3.53395,2.89624,
4.37966,4.85147,4.74207,3.74192,5.07493,2.35153,3.86664,5.48155,2.99182,3.98548,
3.22550,2.76977,2.09944,2.59087,4.05865,5.28144,5.52691,1.19130,0.67274,1.18344,
2.33713,4.25945,0.77823,5.57025,3.74692,3.05465,2.42353,4.82597,2.39986,4.47778,
0.58362,2.52318,2.04610,3.21699,0.97332,5.40335,3.33817,4.80078,4.48832,3.51377,
2.54389,4.65517,4.14499,4.46535,2.42719,2.32712,0.94533,3.59604,2.96302,0.97271,
2.86833,0.85168,3.07548,0.60146,4.37278,1.65569,4.52029,2.42595,1.42498,3.43791,
2.09587,5.43381,1.41063,3.02654,1.40605,4.67694,3.57717,3.71152,1.91024,5.44965,
4.88588,4.59974,2.87227,2.34291,1.26337,2.98660,1.92945,1.99250,5.10216,2.47679,
1.52002,1.64555,5.12012,3.78397,1.81320,0.69223,3.71549,1.21074,0.86082,4.15962,
3.00398,3.44855,0.93753,1.03050,2.71429,2.72296,0.93642,2.93348,2.28346,3.74759,
1.12397,4.97137,5.04276,2.51386,1.45904,3.10280,1.97533,3.67302,3.15439,4.95684,
2.48327,4.87766,5.16564,5.07953,4.38759,1.94518,0.98307,4.24881,0.90355,2.15558,
5.29357,2.18481,2.67792,0.78640,4.77473,4.77175,0.90384,2.43581,3.54833,4.55512,
5.55844,1.60974,4.39035,4.92409,2.03792,1.97835,4.88780,2.41289,5.17198,5.28545,
4.17032,4.03154,2.56418,5.15101,0.99449,3.91424,3.66601,2.48822,1.23582,1.73389,
5.55478,1.87154,5.05722,1.45517,2.78292,5.17646,1.09861,2.77579,4.18870,1.80546,
2.19212,2.95824,2.76868,0.61975,3.00695,1.35810,5.19147,5.27144,3.44188,1.64415])

create_table(sample)
create_sorted_table(sample)

sample.sort()

a = 0.58
b = 5.58
alpha = 0.05

table1 = create_table1(sample, a, b)
plot_empirical_cdf(sample, a, b)

D_crit = 1.358099
D = table1['D_N*sqrt(N)'].item()
if D > D_crit:
    print("Гипотеза отвергнута")
else:
    print("Гипотеза не отвергнута")