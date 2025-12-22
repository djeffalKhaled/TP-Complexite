import matplotlib.pyplot as plt

def read_data(filename):
    N = []
    T = []
    P = []
    with open(filename) as f:
        for line in f:
            n, t, p = line.split()
            N.append(int(n))
            T.append(float(t))
            P.append(int(p))
    return N, T

# les fichiers resultats
files = ["results/A1_results.txt", "results/A2_results.txt", "results/A3_results.txt", "results/A4_results.txt"]

plt.figure(figsize=(8,6))
plt.ticklabel_format(style='plain', axis='x')
for file in files:
    N, T = read_data(file)
    plt.scatter(N, T, s=20, label=file)

plt.xlabel("Nombre")
plt.ylabel("Temps d'execution")
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend()
plt.tight_layout()  
plt.show()



max_times = []
labels = []

for file in files:
    with open(file) as f:
        temps = [float(line.split()[1]) for line in f]  
    max_times.append(max(temps))  
    labels.append(file.split("/")[-1].replace("_results.txt",""))

plt.figure(figsize=(8,6))
plt.bar(labels, max_times, color=['skyblue','salmon','lightgreen','orange'])
plt.xlabel("Algorithmes")
plt.ylabel("Temps d'exécution maximal (s)")
plt.title("Temps d'exécution maximal par algorithme")
plt.grid(axis='y', linestyle='--', alpha=0.5)

for i, v in enumerate(max_times):
    plt.text(i, v + 0.00001, f"{v:.6f}", ha='center')  

plt.show()

plt.figure(figsize=(10,7))  

colors = ['red', 'blue', 'green', 'orange']
for file, color in zip(files, colors):
    N, T = read_data(file)
    digits = [len(str(n)) for n in N]
    plt.scatter(digits, T, s=30, color=color, label=file.split("/")[-1].replace("_results.txt",""))

plt.xlabel("Nombre de chiffres de N", fontsize=24)
plt.ylabel("Temps d'exécution (s)", fontsize=24)
plt.title("Temps d'exécution des algorithmes selon le nombre de chiffres de N", fontsize=24)
plt.grid(True, linestyle="--", linewidth=0.5)
plt.xticks(range(min(digits), max(digits)+1), fontsize=18) 
plt.yticks(fontsize=18)  #
plt.legend(fontsize=16)
plt.tight_layout()
plt.show()


import matplotlib.pyplot as plt
from collections import defaultdict

def read_data(filename):
    N = []
    T = []
    with open(filename) as f:
        for line in f:
            n, t = line.split()
            N.append(int(n))
            T.append(float(t))
    return N, T



import matplotlib.pyplot as plt
from collections import defaultdict

def read_data(filename):
    N = []
    T = []
    with open(filename) as f:
        for line in f:
            n, t = line.split()
            N.append(int(n))
            T.append(float(t))
    return N, T

files = ["results/A1_results.txt", "results/A2_results.txt", 
         "results/A3_results.txt", "results/A4_results.txt"]

# Collect max time per number of digits per algorithm
digit_max_times = defaultdict(lambda: [0]*len(files))  

for idx, file in enumerate(files):
    N, T = read_data(file)
    for n, t in zip(N, T):
        d = len(str(n))
        if t > digit_max_times[d][idx]:
            digit_max_times[d][idx] = t

digits = sorted(digit_max_times.keys())
width = 0.2
colors = ['skyblue', 'salmon', 'lightgreen', 'orange']

plt.figure(figsize=(14,6))

for i, color in enumerate(colors):
    # convert seconds to microseconds
    max_times_us = [digit_max_times[d][i]*1e6 for d in digits]
    positions = [d + i*width for d in digits]
    plt.bar(positions, max_times_us, width=width, label=f"A{i+1}", color=color)
    for x, y in zip(positions, max_times_us):
        plt.text(x, y*1.05, f"{y:.2f}", ha='center', va='bottom', fontsize=8)

plt.xlabel("Nombre de chiffres de N", fontsize=14)
plt.ylabel("Temps d'exécution maximal (μs)", fontsize=14)
plt.title("Max temps d'exécution par nombre de chiffres et par algorithme", fontsize=16)
plt.xticks([d + 1.5*width for d in digits], digits)
plt.grid(axis='y', linestyle='--', alpha=0.5)
plt.legend()
plt.tight_layout()
plt.show()
