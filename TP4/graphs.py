import matplotlib.pyplot as plt

sizes = []
tri_bulle = []
tri_bulle_opt = []
tri_tas = []
tri_rapide = []
tri_distribution = []
tri_gnome = []

with open("resultats.txt") as f:
    lines = [line.strip() for line in f if line.strip()]

i = 0
while i < len(lines):
    sizes.append(int(lines[i].split()[-1]))
    tri_bulle.append(float(lines[i+1].split()[2]))
    tri_bulle_opt.append(float(lines[i+2].split()[3]))
    tri_tas.append(float(lines[i+3].split()[3]))
    tri_rapide.append(float(lines[i+4].split()[2]))
    tri_distribution.append(float(lines[i+5].split()[3]))
    tri_gnome.append(float(lines[i+6].split()[2]))
    i += 7

plt.plot(sizes, tri_bulle, marker='o', label="Tri Bulle")
plt.plot(sizes, tri_bulle_opt, marker='o', label="Tri Bulle Opt")
plt.plot(sizes, tri_tas, marker='o', label="Tri par Tas")
plt.plot(sizes, tri_rapide, marker='o', label="Tri rapide")
plt.plot(sizes, tri_distribution, marker='o', label="Tri par Distribution")
plt.plot(sizes, tri_gnome, marker='o', label="Tri Gnome")

plt.xlabel("Taille du tableau")
plt.ylabel("Temps (s)")
plt.title("Temps d'exécution des algorithmes de tri")
plt.legend()
plt.grid(True)
plt.savefig("algorithmes_des_tris.png")
