import numpy as np
import pandas as pd
from openpyxl import Workbook
import matplotlib.pyplot as plt
from scipy.stats import expon
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

def plot_empirical_cdf(sample):
    sorted_sample = np.sort(sample)


    n = len(sample)
    cumulative_probabilities = np.arange(1, n + 1) / n


    plt.figure(figsize=(10, 6))
    plt.step(sorted_sample, cumulative_probabilities, where='post', color='blue', linewidth=2) 


    plt.xlabel("Значение")
    plt.ylabel("Эмпирическая функция распределения")
    plt.title("Эмпирическая функция распределения (Экспоненциальное)")
    plt.grid(True)

    plt.xlim(left=0, right=sorted_sample.max() * 1.1) 


    plt.show()

def create_interval_series(sample, num_intervals):
    min_sample = 0
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
        'ni': interval_counts
    })
    N = len(sample)
    interval_series['wi'] = interval_series['ni'] / N
    grouped = interval_series
    total_ni = grouped['ni'].sum()
    total_wi = grouped['wi'].sum()
    total_row = pd.DataFrame([{'interval': '', 'ni': total_ni, 'wi': total_wi}])
    big_grouped = pd.concat([grouped, total_row], ignore_index=True)
    big_grouped.to_excel("interval_table.xlsx", index=False)
    return grouped

def create_comprasion_table(grouped, lamb):  
    res = grouped[['interval', 'wi']].copy()  
    theoretical_probabilities = []
    for interval in res['interval'].values:
        lower_bound = interval.left
        upper_bound = interval.right
        prob = expon.cdf(upper_bound, scale=1/lamb) - expon.cdf(lower_bound, scale = 1/lamb)
        theoretical_probabilities.append(prob)

    res['pi'] = theoretical_probabilities 
    res['dif'] = res['wi'] - res['pi'] 
    total_wi = res['wi'].sum()
    total_pi = res['pi'].sum()
    max_dif = np.max(np.abs(res['dif'])) 
    total_row = pd.DataFrame([{'interval': '', 'wi': total_wi, 'pi': total_pi, 'dif': max_dif}])
    res = pd.concat([res, total_row], ignore_index=True)
    res.to_excel("comprasion_table.xlsx", index=False)
    return grouped

def create_associated_series(interval_series):

    associated_series = interval_series.copy()
    associated_series['xi'] = associated_series['interval'].apply(lambda x: (x.left + x.right) / 2) 
    associated_series = associated_series[['xi', 'ni', 'wi']] 
    total_ni = associated_series['ni'].sum()
    total_wi = associated_series['wi'].sum()
    total_row = pd.DataFrame([{'xi': '', 'ni': total_ni, 'wi': total_wi}])
    big_associated_series = pd.concat([associated_series, total_row], ignore_index=True)
    big_associated_series.to_excel("associated_table.xlsx", index=False)
    return associated_series

def plot_hystogramm(interval_series, lambda_p):
    xi = interval_series['interval'].apply(lambda x: (x.left + x.right) / 2)
    h = interval_series['interval'].apply(lambda x: x.right - x.left).astype(float)

    plt.figure(figsize=(10, 6))
    plt.bar(xi, interval_series['wi'] / h, width=h, color='blue')

    x = np.linspace(interval_series['interval'].iloc[0].left, interval_series['interval'].iloc[-1].right, 200)
    pdf = expon.pdf(x, scale=1/lambda_p)
    plt.plot(x, pdf, 'r-', linewidth=2, label=f"График плотности распределения")

    plt.ylabel("Относительная частота")
    plt.title("Гистограмма ассоциированного ряда")
    plt.xticks([0]+[interval.right for interval in interval_series['interval']])
    plt.grid(True)
    plt.show()


N = 200
h = 1.114
n = 8

sample = np.random.exponential(1 / h, N)
create_table(sample)
create_sorted_table(sample)

interval_series = create_interval_series(sample, n)
create_comprasion_table(interval_series, h)
associated_series = create_associated_series(interval_series)

x = associated_series['xi']
w = associated_series['wi']
l = len(x)

avg = 0
avg_2 = 0
avg_3 = 0
avg_4 = 0
d = 0
interval_widths = [interval.right - interval.left for interval in interval_series['interval']]
h = np.mean(interval_widths)

for i in range(l):
    avg += x[i]*w[i]
    avg_2 += x[i]**2*w[i]
    avg_3 += x[i]**3*w[i]
    avg_4 += x[i]**4*w[i]

for i in range(l):
    d += ((x[i]-avg)**2)*w[i]
d -= h**2/12
g1 = (avg_3 - 3*avg_2*avg + 2*avg**3)/(d**1.5)
g2 =  (avg_4 - 4*avg_3*avg + 6*avg_2*avg**2 - 3*avg**4)/(d**2) - 3

moda = x[np.argmax(w)]


cumulative_wi = np.cumsum(w)
median_index = np.where(cumulative_wi >= 0.5)[0][0]
median = x[median_index]

print('Выборочное среднее: ', avg)
print('Выборочное дисперсия с поправкой Шеппарда: ', d)
print('Выборочное среднее квадратическое отклонение: ', math.sqrt(d))
print('Выборочная мода: ', moda)
print('Выборочная медиана: ', median)
print('Выборочный коэффициент асимметрии: ', g1)
print('Выборочный коэффициент эксцесса: ', g2)


plot_empirical_cdf(sample)
plot_hystogramm(interval_series, h)