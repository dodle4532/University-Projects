import numpy as np
import pandas as pd
from openpyxl import Workbook
import matplotlib.pyplot as plt
from scipy.stats import geom
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

def create_statistical_table(sample):
    value_counts = pd.Series(sample).value_counts().reset_index()
    value_counts.columns = ['xi', 'ni']
    value_counts = value_counts.sort_values('xi')
    value_counts['wi'] = value_counts['ni'] / len(sample)
    value_counts['s'] = value_counts['wi'].cumsum()
    total_ni = value_counts['ni'].sum()
    total_wi = value_counts['wi'].sum()
    total_row = pd.DataFrame([{'xi': '', 'ni': total_ni, 'wi': total_wi, 's': '-'}])
    grouped = pd.concat([value_counts, total_row], ignore_index=True)
    grouped = grouped[['xi', 'ni', 'wi', 's']]
    grouped.to_excel("statistical_table.xlsx", index=False)
    return grouped

def create_comprasion_table(grouped, p):
    res = grouped[['xi', 'wi']].iloc[:-1].copy()
    theoretical_probabilities = []
    for i in res['xi'].values:
        theoretical_probabilities.append((1-p)**i*p)
    res['pi'] = theoretical_probabilities
    res['dif'] = res['wi'] - theoretical_probabilities
    total_wi = res['wi'].sum()
    total_pi = res['pi'].sum()
    total_row = pd.DataFrame([{'xi': '', 'wi': total_wi, 'pi': total_pi, 'dif': np.max(res['dif'])}])
    res = pd.concat([res, total_row], ignore_index=True)
    res.to_excel("comprasion_table.xlsx", index = False)
    return grouped

def plot_relative_frequency_polygon(df, n, p):
    df = df.drop(df.index[-1])
    x = np.arange(0, n + 1) 
    theoretical_probabilities = []
    for i in range(n+1):
        theoretical_probabilities.append(p*(1-p)**i)
    plt.figure(figsize=(12, 7))
    plt.plot(df['xi'], df['wi'], marker='o', linestyle='-', label='Полигон относительных частот')
    plt.plot(x, theoretical_probabilities, marker='x', linestyle='--', color='red', label='Полигон теоретических вероятностей')
    plt.xlabel("Значение xi")
    plt.ylabel("Относительная частота / Вероятность")
    plt.title("Полигон относительных частот и полигон теоретических вероятностей")
    plt.grid(True)
    plt.legend()
    plt.show()

def plot_empirical_cdf(df):
    df = df.drop(df.index[-1])
    x = []
    y = []


    for i, row in df.iterrows():
        x.append(row['xi']) 
        y.append(row['s']) 


    plt.figure(figsize=(10, 6))
    prevX = x[0]
    for i in range(1, len(x)):
        if y[i] == y[i-1]:
            continue
        plt.arrow(prevX, y[i-1], x[i] - prevX, 0, color='blue', head_width=0.02, head_length=0.05, length_includes_head=True, width = 0.001)
        prevX = x[i]


    plt.xlabel("Значение xi")
    plt.ylabel("Эмпирическая функция распределения")
    plt.title("Эмпирическая функция распределения")
    plt.grid(True)


    plt.show()


N = 20000
n = 23
p = 0.314
sample = np.random.geometric(p, N) - 1
create_table(sample)
create_sorted_table(sample)
statistical_table = create_statistical_table(sample)
create_comprasion_table(statistical_table, p)
x = statistical_table['xi'].values[:-1]
w = statistical_table['wi'].values[:-1]
l = len(x)

avg = 0
avg_2 = 0
avg_3 = 0
avg_4 = 0
for i in range(l):
    avg += x[i]*w[i]
    avg_2 += x[i]**2*w[i]
    avg_3 += x[i]**3*w[i]
    avg_4 += x[i]**4*w[i]

d = avg_2-avg**2

moda = x[0]
max = w[0]
for i in range(l):
    if w[i] > max:
        moda = x[i]
        max = w[i]

median = None
for i in range(len(statistical_table)):
    if statistical_table['s'][i] >= 0.5:
        median = statistical_table['xi'][i]
        break

g1 = (avg_3 - 3*avg_2*avg + 2*avg**3)/d**1.5
g2 =  (avg_4 - 4*avg_3*avg + 6*avg_2*avg**2 - 3*avg**4)/d**2 - 3
print('Выборочное среднее: ', avg)
print('Выборочное дисперсия: ', d)
print('Выборочное среднее квадратическое отклонение: ', math.sqrt(d))
print('Выборочная мода: ', moda)
print('Выборочная медиана: ', median)
print('Выборочный коэффициент асимметрии: ', g1)
print('Выборочный коэффициент эксцесса: ', g2)
plot_relative_frequency_polygon(statistical_table, n, p)
plot_empirical_cdf(statistical_table)