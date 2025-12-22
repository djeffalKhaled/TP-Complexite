import matplotlib.pyplot as plt

def read_data(filename):
    N = []
    T = []
    with open(filename) as f:
        for line in f:
            n, t = line.split()
            N.append(int(n))
            T.append(float(t))
    return N, T

files = ["A1_Tab.txt", "A2_Tab.txt", "A3_Tab.txt", "A4_Tab.txt"]
algo_names = ["A1", "A2", "A3", "A4"]
linestyles = ["-", "--", "-.", ":"]
colors = ["blue", "orange", "red", "green"]

# ---- 2) A1 vs A2 ----
plt.figure(figsize=(12,6))
plt.ticklabel_format(style='plain', axis='x')
for i in range(2):  # A1 + A2
    N, T = read_data(files[i])
    plt.plot(N, T, linestyle=linestyles[i], marker='o', linewidth=2, markersize=7,
             label=algo_names[i], color=colors[i])

plt.xlabel("Nombre", fontsize=18)
plt.ylabel("Temps d'execution (s)", fontsize=18)
plt.title("A1 vs A2", fontsize=22)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend(fontsize=16)
plt.tight_layout()
plt.show()

# ---- 3) A1 vs A2 vs A3 ----
plt.figure(figsize=(12,6))
plt.ticklabel_format(style='plain', axis='x')
for i in range(3):  # A1 + A2 + A3
    N, T = read_data(files[i])
    plt.plot(N, T, linestyle=linestyles[i], marker='o', linewidth=2, markersize=7,
             label=algo_names[i], color=colors[i])

plt.xlabel("Nombre", fontsize=18)
plt.ylabel("Temps d'execution (s)", fontsize=18)
plt.title("A1 vs A2 vs A3", fontsize=22)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend(fontsize=16)
plt.tight_layout()
plt.show()

# Individual graphs
for file, style, color, algo_name in zip(files, linestyles, colors, algo_names):
    N, T = read_data(file)
    plt.figure(figsize=(12,6))
    plt.ticklabel_format(style='plain', axis='x')
    plt.plot(N, T, linestyle=style, marker='o', linewidth=2, markersize=7, label=file, color=color)
    plt.xlabel("Nombre", fontsize=18)
    plt.ylabel("Temps d'execution (s)", fontsize=18)
    plt.title(f"Temps d'execution de l'algorithme {algo_name}", fontsize=22)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.legend(fontsize=16)
    plt.tight_layout()
    plt.show()

# Combined graph
plt.figure(figsize=(12,6))
for file, style, color in zip(files, linestyles, colors):
    N, T = read_data(file)
    plt.ticklabel_format(style='plain', axis='x')
    plt.plot(N, T, linestyle=style, marker='o', linewidth=2, markersize=7, label=file, color=color)

plt.xlabel("Nombre", fontsize=18)
plt.ylabel("Temps d'execution (s)", fontsize=18)
plt.title("Temps d'execution des algorithmes", fontsize=22)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend(fontsize=16)
plt.tight_layout()
plt.show()

# Histogram of max times
max_times = []
labels = []

for file in files:
    with open(file) as f:
        temps = [float(line.split()[1]) for line in f]
    max_times.append(max(temps))
    labels.append(file.replace("_results.txt", ""))

plt.figure(figsize=(14,10))
plt.bar(labels, max_times, color=['skyblue','salmon','lightgreen','orange'])

plt.xlabel("Algorithmes", fontsize=18)
plt.ylabel("Temps d'exécution maximal (s)", fontsize=18)
plt.title("Temps d'execution maximal par algorithme", fontsize=22)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.grid(axis='y', linestyle='--', alpha=0.5)

for i, v in enumerate(max_times):
    plt.text(i, v + (v * 0.02), f"{v:.6f}", ha='center', fontsize=16)

plt.tight_layout()
plt.show()


import matplotlib.pyplot as plt

def read_data(filename):
    N = []
    T = []
    with open(filename) as f:
        for line in f:
            n, t = line.split()
            N.append(int(n))
            T.append(float(t))
    return N, T


files = ["A3_Tab.txt", "A4_Tab.txt"]
names = ["A3", "A4"]
linestyles = ["-.", ":"]
colors = ["red", "green"]

plt.figure(figsize=(12,6))

for file, name, style, color in zip(files, names, linestyles, colors):
    N, T = read_data(file)

    plt.plot(N, T,
             linestyle=style,
             marker='o',
             linewidth=2,
             markersize=7,
             label=name,
             color=color)
    
plt.xlabel("Nombre", fontsize=18)
plt.ylabel("Temps d'exécution (s)", fontsize=18)
plt.title("A4 vs A3", fontsize=22)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend(fontsize=16)
plt.tight_layout()
plt.show()

