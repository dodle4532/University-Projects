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

def create_interval_series(sample, num_intervals):

    min_sample = np.min(sample)
    max_sample = np.max(sample)
    range_sample = max_sample - min_sample
    interval_width = range_sample / num_intervals
    borders = [min_sample + i * interval_width for i in range(num_intervals + 1)]
    intervals = []
    for i in range(num_intervals):
        left = round(borders[i],5)
        right = round(borders[i + 1],5)
        interval = pd.Interval(left=left, right=right, closed="right") 
        intervals.append(interval)
    interval_indices = np.digitize(sample, borders[1:-1], right=True) 
    interval_counts = np.bincount(interval_indices, minlength=len(intervals))
    interval_series = pd.DataFrame({
        'interval': intervals,
        'n_k': interval_counts
    })
    N = len(sample)
    interval_series['w_k'] = interval_series['n_k'] / N
    grouped = interval_series
    total_ni = grouped['n_k'].sum()
    total_wi = grouped['w_k'].sum()
    total_row = pd.DataFrame([{'interval': '', 'n_k': total_ni, 'w_k': total_wi}])
    big_grouped = pd.concat([grouped, total_row], ignore_index=True)
    big_grouped.to_excel("interval_table.xlsx", index=False)
    return grouped

def create_table2(interval_series, avg, sigma):
    a = []
    intervals = interval_series['interval']
    for interval in intervals:
        a.append(interval.left)
    a.append(intervals.iloc[-1].right)
    k = np.arange(0, len(a))
    col3 = (a - avg) / sigma
    p_k = [None]
    for i in range(1, len(a)):
        if i == 1:
            p_k.append(norm.cdf(col3[1]))
        elif i == len(a) - 1:
            p_k.append(1 - norm.cdf(col3[len(a)-2]))
        else:
            p_k.append(norm.cdf(col3[i]) - norm.cdf(col3[i-1]))
    col4 = []
    for i in col3:
        col4.append(1/sigma * 1/(math.sqrt(2*math.pi))*math.exp(-i**2/2))
    table = pd.DataFrame( {
        'k': k,
        'a_k': a,
        '(a_k - avg)/sigma': col3,
        '4': col4,
        '5': norm.cdf(col3),
        'p_k': p_k
    })
    total_p_k = table['p_k'].sum() 
    total_row = pd.DataFrame( [{'k': '', 'a_k': '', '(a_k - avg)/sigma': '', '4': '', '5': '', 'p_k': total_p_k}])
    table = pd.concat([table, total_row], ignore_index=True)
    table.to_excel("table4_2.xlsx", index=False)
    return table

def plot_normal_distribution_with_histogram(interval_series, avg, sigma):
    intervals = interval_series['interval']  
    w_k = interval_series['w_k']  
    bin_edges = [interval.left for interval in intervals]
    bin_edges.append(intervals.iloc[-1].right)  
    bin_edges = np.array(bin_edges)
    plt.figure(figsize=(10, 6))
    plt.bar(bin_edges[:-1], w_k, width=np.diff(bin_edges), align='edge', alpha=0.6, color='skyblue', label='Гистограмма')
    xmin, xmax = plt.xlim()
    x = np.linspace(xmin, xmax, 100)
    p = norm.pdf(x, avg, sigma)
    plt.plot(x, p, 'r', linewidth=2, label='Плотность нормального распределения')
    plt.title('Гистограмма и плотность нормального распределения')
    plt.xlabel('Значения')
    plt.ylabel('Плотность / Относительная частота')
    plt.legend()
    plt.grid(True)
    plt.show()

def create_table3(interval_series, avg, sigma, size):
    intervals = interval_series['interval']
    k = np.arange(1, intervals.size+1)
    interval_series_with_k = interval_series.copy()
    interval_series_with_k['k'] = k
    res = interval_series_with_k[['k', 'interval', 'w_k']].copy()
    p_k = [norm.cdf((interval.right-avg)/sigma) - norm.cdf((interval.left-avg)/sigma) for interval in intervals]
    res['p_k'] = p_k
    res['dif'] = np.abs(res['w_k']-res['p_k'])
    res['6'] = size * res['dif']**2/res['p_k']
    max_dif = np.max(res['dif'])
    total_wk = res['w_k'].sum()
    total_pk = res['p_k'].sum() 
    total6 = res['6'].sum()
    total_row = pd.DataFrame([{'k' : '', 'interval': '', 'w_k': total_wk, 'p_k': total_pk, 'dif': max_dif, '6' : total6}])
    res = pd.concat([res, total_row], ignore_index=True)
    res.to_excel("table4_3.xlsx", index=False)
    return res

n = 8

sample = np.array([
-0.35319,0.67050,3.28565,1.75772,2.26159,2.18680,4.35132,0.02902,1.79163,2.64390,
3.87812,2.04162,2.67021,2.38500,1.08521,2.18478,1.02831,0.95976,2.59487,1.87637,
3.46145,1.30609,0.13458,1.35363,2.46486,2.71883,0.11349,4.23509,1.53353,0.76606,
-0.52306,1.55661,0.04814,3.31585,1.81806,1.67291,1.41088,-0.37021,0.89168,0.90307,
2.60667,3.13860,2.39235,2.14426,2.64293,0.21744,2.71156,0.21635,0.51326,1.71568,
-1.36922,2.31949,1.34816,0.66422,1.96820,2.89083,1.11448,3.26231,0.92168,0.97945,
0.60188,0.40433,5.03433,1.37509,1.83173,1.52859,-0.69152,3.24312,3.07837,2.88186,
1.63916,2.86765,1.50226,1.16751,1.34941,0.33445,1.76847,1.41619,1.38032,2.58211,
2.43292,-0.11520,-0.97794,2.53527,3.01750,2.66244,-1.40950,1.47793,2.46935,0.35374,
2.29257,-0.96679,2.24708,3.29181,0.18227,3.30234,2.25312,0.82286,0.70665,-1.93410,
2.93132,1.65284,-0.73309,-2.76601,2.23082,-0.06830,1.46044,2.90257,0.38346,-0.24683,
1.03768,0.90566,5.45633,0.22535,-0.33776,1.75757,0.74655,4.06908,1.14494,2.13721,
1.98196,-0.41657,0.40346,1.45121,1.96879,0.65668,0.77729,1.94001,2.06009,1.89094,
4.06745,1.69644,0.45294,0.25100,2.15031,0.19924,-0.14499,1.79545,0.48271,2.38058,
2.81173,1.85969,0.54444,0.86312,0.81711,2.90022,-0.30595,-0.08786,1.28431,0.56956,
1.51394,-0.19003,1.43700,1.90238,-0.99506,2.55284,1.61840,1.61983,1.77842,1.57263,
2.97090,1.26141,2.83559,2.23720,1.97463,-0.68673,-1.11565,2.50110,2.13355,0.57220,
-0.49380,1.38311,0.73993,-0.37772,2.51722,4.19842,0.87829,0.40752,1.33957,1.13171,
0.60670,1.36902,0.26082,-1.32240,3.57378,1.80512,2.70523,0.69886,1.09151,-0.63845,
3.95989,0.39874,2.97671,0.61669,-1.04132,0.08427,2.16377,1.37692,2.45751,1.89524])

create_table(sample)
create_sorted_table(sample)

sample.sort()
interval_series = create_interval_series(sample, n)


avg = round(sample.sum() / sample.size,5)

interval_widths = [interval.right - interval.left for interval in interval_series['interval']]
h = np.mean(interval_widths)
avg_2 = 0
for i in sample:
    avg_2 += i**2
avg_2 /= sample.size
avg_2 -= h**2/12 + avg**2
avg_2 = round(avg_2, 5)
sigma = round(math.sqrt(avg_2),5)

table_2 = create_table2(interval_series, avg, sigma)
plot_normal_distribution_with_histogram(interval_series, avg, sigma)
table_3 = create_table3(interval_series, avg, sigma, sample.size)

critical_value = 10.191028
my_chi2 = table_3['6'].iloc[-1]
if my_chi2 > critical_value:
    print("Гипотеза отвергнута")
else:
    print("Гипотеза не отвергнута")