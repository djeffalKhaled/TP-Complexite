import pandas as pd
import matplotlib.pyplot as plt

# Charger le fichier de résultats
df = pd.read_csv("results_partB.txt", sep="\t", comment='#', encoding='utf-16-le')


# On ne garde que les lignes type "rand"
df_rand = df[df["type"] == "rand"]

# Extraire les colonnes
n = df_rand["n"]
naive_cmp = df_rand["Naive_Cmp"]
pair_cmp = df_rand["Pair_Cmp"]
naive_time = df_rand["Naive_Time(s)"]
pair_time = df_rand["Pair_Time(s)"]

# ---------- GRAPHE 1 : Comparaisons ----------
plt.figure(figsize=(10,6))
plt.plot(n, naive_cmp, marker='o', label="Naive Comparisons")
plt.plot(n, pair_cmp, marker='o', label="Pair Comparisons")

plt.title("Comparaison du nombre de comparaisons (Partie B)")
plt.xlabel("Taille n du tableau")
plt.ylabel("Nombre de comparaisons")
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()
plt.savefig("comparisons_partB.png", dpi=300)
plt.close()

# ---------- GRAPHE 2 : Temps ----------
plt.figure(figsize=(10,6))
plt.plot(n, naive_time, marker='o', label="Naive Time (s)")
plt.plot(n, pair_time, marker='o', label="Pair Time (s)")

plt.title("Temps d'exécution (Partie B)")
plt.xlabel("Taille n du tableau")
plt.ylabel("Temps (secondes)")
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()
plt.savefig("time_partB.png", dpi=300)
plt.close()

print("Graphiques générés : comparisons_partB.png et time_partB.png")
