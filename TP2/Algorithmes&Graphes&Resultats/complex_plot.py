import matplotlib.pyplot as plt

# -----------------------------
# Données
# -----------------------------
n = [100000,200000,400000,600000,800000,
     1000000,1200000,1400000,1600000,1800000]

nontries_pire = [0.00120,0.00240,0.00480,0.00720,0.00960,
                 0.01200,0.01440,0.01680,0.01920,0.02160]

tries_pire = [0.00095,0.00190,0.00380,0.00570,0.00760,
              0.00950,0.01140,0.01330,0.01520,0.01710]

dicho_pire = [0.000006,0.000007,0.000009,0.000010,0.000011,
              0.000012,0.000013,0.000014,0.000015,0.000016]

# -----------------------------
# Palette creamy+ (plus visible)
# -----------------------------
c1 = "#d6896f"   # Terracotta pastel (plus visible)
c2 = "#7fb77e"   # Green sage saturé
c3 = "#6faed9"   # Baby blue saturé et propre

plt.figure(figsize=(10,6), dpi=140)

# -----------------------------
# Courbes avec texture
# -----------------------------
plt.plot(n, nontries_pire, marker='o', markersize=7,
         linewidth=2.8, color=c1, label="Non trié – Pire cas")

plt.plot(n, tries_pire, marker='o', markersize=7,
         linewidth=2.8, color=c2, label="Trié séquentiel – Pire cas")

plt.plot(n, dicho_pire, marker='o', markersize=7,
         linewidth=2.8, color=c3, label="Dichotomique – Pire cas")

# -----------------------------
# Style Global (modern + clean)
# -----------------------------
plt.title("T(n) — Pire Cas", fontsize=19, weight='bold', pad=12)
plt.xlabel("Taille du tableau (n)", fontsize=14)
plt.ylabel("Temps (secondes)", fontsize=14)

# Grille texturée légère
plt.grid(True, linestyle='--', linewidth=0.6, alpha=0.35)

# Ticks lisibles
plt.xticks(n, rotation=25)
plt.yticks(fontsize=12)

# Legende douce et moderne
plt.legend(fontsize=12, frameon=True, edgecolor="#E0E0E0")

plt.tight_layout()
plt.show()
