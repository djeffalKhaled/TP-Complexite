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

# les fichiers resultats
files = ["A1_Tab.txt", "A2_Tab.txt", "A3_Tab.txt", "A4_Tab.txt"]

plt.figure(figsize=(14,6))
for file in files:
    N, T = read_data(file)
    plt.scatter(N, T, s=20, label=file)

plt.xlabel("Nombre")
plt.ylabel("Temps d'execution")
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend()
plt.tight_layout()
plt.show()

