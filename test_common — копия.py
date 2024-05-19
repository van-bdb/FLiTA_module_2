import numpy as np
import pandas as pd
#pd.set_option('display.precision', 2)
import matplotlib.pyplot as plt
from itertools import zip_longest as zip_l, cycle
import subprocess
import re
from random import randint
pattern = re.compile(r"\t(.*?)\n")

def gettime(lenght):
    process = subprocess.Popen(["common.exe", "testarr.txt", str(lenght)], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    output, _ = process.communicate()
    output = output.decode()
    print(output)
    match = pattern.findall(output)[0]
    return float(match)

def mkdata(lenght, divercity):
    with open("testarr.txt", "wt") as f:
        for i in range(lenght):
            f.write(f"{randint(0, divercity)}\n")
    
def getframe(lenghts):
    return pd.DataFrame({'x': lenghts, 'y': [gettime(i) for i in lenghts]})

def plot(df, function):
    x_l = list(df['x'])
    y_l = list(df['y'])
    index0_25 = sorted(x_l)[len(x_l)//4]
    k = y_l[x_l.index(index0_25)] / function(index0_25)
    plt.plot(df['x'], df['y'], 'bo', markersize=4, label='Measured')
    plt.plot(df['x'], [function(i)*k for i in  df['x']], 'b--', linewidth=1, label='Calculated')
    plt.xlabel("array lenght, items")
    plt.ylabel("time, seconds")

last_df = None

def generate(upto, expectation_f, point_c=21, df=None):
    gap_len = upto//(point_c-1)
    if df is None:
        df = getframe(range(0, gap_len*point_c, gap_len))
    plot(df, expectation_f)
    plt.show()
    global last_df
    last_df = df
    return df
    

#generate(10000000, lambda x:x)
