import matplotlib.pyplot as plt

def read_data(filename):
    N, T, P = [], [], []
    with open(filename) as f:
        for line in f:
            n, t, p = line.split()
            N.append(int(n))
            T.append(float(t))
            P.append(int(p))
    return T, P

files = ["results/A1_results.txt", "results/A2_results.txt", "results/A3_results.txt", "results/A4_results.txt"]

max_prime_times = []
max_nonprime_times = []

for file in files:
    T, P = read_data(file)
    prime_times = [t for t, p in zip(T, P) if p == 1]
    nonprime_times = [t for t, p in zip(T, P) if p == 0]
    max_prime_times.append(max(prime_times) if prime_times else 0)
    max_nonprime_times.append(max(nonprime_times) if nonprime_times else 0)

labels = ["A1", "A2", "A3", "A4"]

x = range(len(labels))
plt.figure(figsize=(10,6))
plt.bar([i-0.15 for i in x], max_prime_times, width=0.3, label="Prime", color='red')
plt.bar([i+0.15 for i in x], max_nonprime_times, width=0.3, label="Non-prime", color='blue')
plt.xticks(x, labels)
plt.ylabel("Max Temp d'Execution (second)")
plt.title("Temp d'Execution Maximale du numero primaire/non-primaire")
plt.legend()
plt.show()
