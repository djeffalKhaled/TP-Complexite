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
linestyles = ["-", "--", "-.", ":"]
colors = ["blue", "orange", "red", "green"]

# Individual graphs
for file, style, color in zip(files, linestyles, colors):
    N, T = read_data(file)
    plt.figure(figsize=(14,6))
    plt.ticklabel_format(style='plain', axis='x')
    plt.plot(N, T, linestyle=style, marker='o', linewidth=2, markersize=7, label=file, color=color)
    plt.xlabel("Nombre", fontsize=18)
    plt.ylabel("Temps d'exécution (s)", fontsize=18)
    plt.title(f"Temps d'exécution — {file}", fontsize=22)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.legend(fontsize=16)
    plt.tight_layout()
    plt.show()

# Combined graph
plt.figure(figsize=(14,6))
for file, style, color in zip(files, linestyles, colors):
    N, T = read_data(file)
    plt.ticklabel_format(style='plain', axis='x')
    plt.plot(N, T, linestyle=style, marker='o', linewidth=2, markersize=7, label=file, color=color)

plt.xlabel("Nombre", fontsize=18)
plt.ylabel("Temps d'exécution (s)", fontsize=18)
plt.title("Temps d'exécution des algorithmes", fontsize=22)
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

plt.figure(figsize=(10,6))
plt.bar(labels, max_times, color=['skyblue','salmon','lightgreen','orange'])

plt.xlabel("Algorithmes", fontsize=18)
plt.ylabel("Temps d'exécution maximal (s)", fontsize=18)
plt.title("Temps d'exécution maximal par algorithme", fontsize=22)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.grid(axis='y', linestyle='--', alpha=0.5)

for i, v in enumerate(max_times):
    plt.text(i, v + (v * 0.02), f"{v:.6f}", ha='center', fontsize=16)

plt.tight_layout()
plt.show()
