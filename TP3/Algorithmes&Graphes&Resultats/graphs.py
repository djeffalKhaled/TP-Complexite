import matplotlib.pyplot as plt

data = []
with open("results.txt") as f:
    for line in f:
        if '|' in line:
            parts = line.split('|')
            sizes = list(map(int, parts[0].split()))
            algo = parts[1].strip()
            time = float(parts[2])
            n, m, np_, mp_ = sizes
            data.append((n, m, np_, mp_, algo, time))

algos = set(row[4] for row in data)

plt.rcParams.update({
    'font.size': 16,
    'lines.linewidth': 2,
    'lines.markersize': 8,
    'axes.grid': True
})

# Graph 1: (n*m)
main_sizes = sorted(set((row[0], row[1]) for row in data), key=lambda x: x[0]*x[1])
x_labels_main = [f"{n}x{m}" for n,m in main_sizes]
x_indices_main = range(len(x_labels_main))

plt.figure(figsize=(10,6))
for algo in algos:
    y = []
    for n,m in main_sizes:
        times = [row[5] for row in data if row[4]==algo and row[0]==n and row[1]==m]
        y.append(sum(times)/len(times))
    plt.plot(x_indices_main, y, marker='o', label=algo)

plt.xticks(x_indices_main, x_labels_main, rotation=45)
plt.xlabel("Taille Matrice A (n x m)")
plt.ylabel("Temp d'Execution (s)")
plt.title("Temp d'Execution vs Taile Matrice A")
plt.legend()
plt.tight_layout()
plt.savefig("graphe_matrice.png")
plt.show()

# Graph 2: (np*mp)
sub_sizes = sorted(set((row[2], row[3]) for row in data), key=lambda x: x[0]*x[1])
x_labels_sub = [f"{np_}x{mp_}" for np_,mp_ in sub_sizes]
x_indices_sub = range(len(x_labels_sub))

plt.figure(figsize=(10,6))
for algo in algos:
    y = []
    for np_,mp_ in sub_sizes:
        times = [row[5] for row in data if row[4]==algo and row[2]==np_ and row[3]==mp_]
        y.append(sum(times)/len(times))
    plt.plot(x_indices_sub, y, marker='o', label=algo)

plt.xticks(x_indices_sub, x_labels_sub, rotation=45)
plt.xlabel("Taille Matrice B (np x mp)")
plt.ylabel("Temp d'Execution (s)")
plt.title("Temp d'Execution vs Taille Matrice B")
plt.legend()
plt.tight_layout()
plt.savefig("graphe_sousmatrice.png")
plt.show()
