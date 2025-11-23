import matplotlib.pyplot as plt

def read_data(filename):
    N = []
    T = []
    with open(filename) as f:
        for line in f:
            n, t = line.split()
            N.append(int(n))
            T.append(float(t))
    data = sorted(zip(N, T))
    N_sorted, T_sorted = zip(*data)
    return N_sorted, T_sorted

# les fichiers resultats
files = ["results/A1_results.txt", "results/A2_results.txt", "results/A3_results.txt", "results/A4_results.txt"]

plt.figure(figsize=(10,6))
for file in files:
    N, T = read_data(file)
    plt.scatter(N, T, s=20, label=file) 

plt.xlabel("Nombre")
plt.ylabel("Temps d'execution")
plt.title("Nuage de points des résultats")
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend()
plt.show()


plt.figure(figsize=(12,8))

for i, file in enumerate(files):
    _, T = read_data(file)
    plt.subplot(2, 2, i+1)
    plt.hist(T, bins=15, edgecolor="black")
    plt.title(file)
    plt.xlabel("Temps")
    plt.ylabel("Nombre de valeurs")
    plt.grid(True, linestyle="--", alpha=0.4)

plt.tight_layout()
plt.show()




max_times = []
labels = []

for file in files:
    with open(file) as f:
        temps = [float(line.split()[1]) for line in f]  # take only T values
    max_times.append(max(temps))  # take the highest time
    labels.append(file.split("/")[-1].replace("_results.txt",""))  # A1, A2, etc.

plt.figure(figsize=(8,6))
plt.bar(labels, max_times, color=['skyblue','salmon','lightgreen','orange'])
plt.xlabel("Algorithmes")
plt.ylabel("Temps d'exécution maximal (s)")
plt.title("Temps d'exécution maximal par algorithme")
plt.grid(axis='y', linestyle='--', alpha=0.5)

for i, v in enumerate(max_times):
    plt.text(i, v + 0.00001, f"{v:.6f}", ha='center')  # show value on top

plt.show()