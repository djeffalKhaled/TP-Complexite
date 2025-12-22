#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TP3_Fonctions.h"

int main() {
    srand(time(NULL));

    int Ns[] = {100, 500, 1000};
    int Ms[] = {100, 500, 1000};
    int Nps[] = {10, 50, 100};
    int Mps[] = {10, 50, 100}; 

    FILE *f = fopen("results.txt", "w");
    if (!f) {
        perror("Erreur ouverture du fichier");
        return 1;
    }

    printf("-----------------------------------------------\n");
    printf(" n   m   np   mp |  Algorithme  |  Temp (s)\n");
    printf("-----------------------------------------------\n");

    for (int ni = 0; ni < 3; ni++) {
        for (int mi = 0; mi < 3; mi++) {
            for (int npi = 0; npi < 3; npi++) {
                for (int mpi = 0; mpi < 3; mpi++) {
                    int n = Ns[ni], m = Ms[mi];
                    int np = Nps[npi], mp = Mps[mpi];

                    if (np > n || mp > m) continue;

                    int** A = allouer_matrice(n, m);
                    int** B = allouer_matrice(np, mp);

                    remplire_matrice_random(A, n, m);
                    remplire_matrice_random(B, np, mp);
                    force_sous_matrice(A, n, m, B, np, mp);

                    double t1 = measure_temp(A, n, m, B, np, mp, 50, sous_matrice);
                    printf("%3d %3d %3d %3d | %-11s | %10.6f\n", n, m, np, mp, "sous_matrice1", t1);
                    fprintf(f, "%3d %3d %3d %3d | %-11s | %10.6f\n", n, m, np, mp, "sous_matrice1", t1);

                    trier_matrice(A, n, m);
                    trier_matrice(B, np, mp);

                    double t2 = measure_temp(A, n, m, B, np, mp, 70, sous_matrice2);
                    printf("%3d %3d %3d %3d | %-11s | %10.6f\n", n, m, np, mp, "sous_matrice2", t2);
                    fprintf(f, "%3d %3d %3d %3d | %-11s | %10.6f\n", n, m, np, mp, "sous_matrice2", t2);

                    liberer_matrice(A, n);
                    liberer_matrice(B, np);
                }
            }
        }
    }

    fclose(f);
    return 0;
}
