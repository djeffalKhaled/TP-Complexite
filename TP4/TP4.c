
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
void permuter(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// TRI BULLE --------------------------------------
void tribulle(int* T, int n) {
    bool changement = true;

    while (changement == true) {
        changement = false;
        for (int i = 0; i < n-1; i++) {
            if (T[i] > T[i+1]) {
                // permuter
                int temp = T[i];
                T[i] = T[i+1];
                T[i+1] = temp;
                changement = true;
            }
        } 
    }
}

void tribulleopt(int* T, int n) {
    bool changement = true;
    int m = n - 1; 
    while (changement == true) {
        changement = false;
        for (int i = 0; i < m; i++) {
            if (T[i] > T[i+1]) {
                 // permuter
                int temp = T[i];
                T[i] = T[i+1];
                T[i+1] = temp;
                changement = true;   
            }
        }
    }
}


// TRI GNOME -------------------------------------------------
void triGnome(int* T, int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || T[i] >= T[i - 1]) {
            i++;
        }
        else {
            int temp = T[i];
            T[i] = T[i - 1];
            T[i - 1] = temp;
            i--;
        }
    }
}

// TRI PAR DEST -----------------------------------
int cle(int x, int i) {
    int div = 1;
    for (int j = 0; j < i; j++) div *= 10;
    return (x / div) % 10;
}

void triAux(int* T, int n, int i) {
    int count[10] = {0};
    int B[n];

    for (int j = 0; j < n; j++)
        count[cle(T[j], i)]++;

    for (int j = 1; j < 10; j++)
        count[j] += count[j - 1];

    for (int j = n - 1; j >= 0; j--) {
        int k = count[cle(T[j], i)] - 1;
        B[k] = T[j];
        count[cle(T[j], i)]--;
    }

    for (int j = 0; j < n; j++)
        T[j] = B[j];
}

void triParDistribution(int* T, int n) {
    int max = T[0];
    for (int i = 1; i < n; i++)
        if (T[i] > max) max = T[i];

    int digits = 0;
    while (max > 0) {
        digits++;
        max /= 10;
    }

    for (int i = 0; i < digits; i++)
        triAux(T, n, i);
}


// TRI TAS ----------------------------------------------

void entasser(int* T, int n, int i) {
    int max = i;        
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && T[gauche] > T[max])
        max = gauche;
    if (droite < n && T[droite] > T[max])
        max = droite;

    if (max != i) {
        permuter(&T[i], &T[max]);
        entasser(T, n, max);
    }
}

void triParTas(int* T, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasser(T, n, i);

    for (int i = n - 1; i > 0; i--) {
        permuter(&T[0], &T[i]); 
        entasser(T, i, 0);    
    }
}

void remplireValeursRand(int* T, int n) {
    for (int i = 0; i < n; i++)
        T[i] = rand() % 1000000000;
}


// tri rapide -----------------------

int partitionner(int* T, int d, int f) {
    int eltPivot = T[d];
    int i = d - 1;
    int j = f + 1;

    while (1) {
        do { i++; } while (T[i] < eltPivot);
        do { j--; } while (T[j] > eltPivot);

        if (i >= j) return j;
        permuter(&T[i], &T[j]);
    }
}

void triRapide(int* T, int p, int r) {
    if (p < r) {
        int q = partitionner(T, p, r);
        triRapide(T, p, q);
        triRapide(T, q + 1, r);
    }
}

// juste pour reducer les arg
void triRapideDirecte(int* T, int n) {
    triRapide(T, 0, n - 1);
}


void remplirValeursRand(int* T, int n) {
    for (int i = 0; i < n; i++)
        T[i] = rand() % 1000000000;
}

double measure_time(int* T, int n, int repeats, void (*algo)(int*, int)) {
    double total = 0;

    for (int r = 0; r < repeats; r++) {
        int* copy = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) copy[i] = T[i];

        clock_t start = clock();
        algo(copy, n);
        clock_t end = clock();

        total += ((double)(end - start)) / CLOCKS_PER_SEC;
        free(copy);
    }

    return total / repeats;
}
int main() {
    srand(time(NULL));
    int tableauN[] = {50, 100, 200, 500, 1000, 1500, 2000, 5000, 10000, 20000, 50000};
    int nbTailles = sizeof(tableauN) / sizeof(tableauN[0]);
    int repeats = 5;

    FILE* f = fopen("resultats.txt", "w");
    if (!f) {
        return 1;
    }

    for (int i = 0; i < nbTailles; i++) {
        int n = tableauN[i];
        int* T = malloc(sizeof(int) * n);
        remplirValeursRand(T, n);

        double t1 = measure_time(T, n, repeats, tribulle);
        double t2 = measure_time(T, n, repeats, tribulleopt);
        double t3 = measure_time(T, n, repeats, triParTas);
        double t4 = measure_time(T, n, repeats, triRapideDirecte);
        double t5 = measure_time(T, n, repeats, triParDistribution);
        double t6 = measure_time(T, n, repeats, triGnome);

        printf("Tableau de taille %d\n", n);
        printf("Tri Bulle: %.6f s\n", t1);
        printf("Tri Bulle Opt: %.6f s\n", t2);
        printf("Tri par Tas: %.6f s\n", t3);
        printf("Tri rapide: %.6f s\n", t4);
        printf("Tri par Distribution: %.6f s\n", t5);
        printf("Tri Gnome: %.6f s\n", t6);
        printf("\n");

        // pour fichier resultat
        fprintf(f, "Tableau de taille %d\n", n);
        fprintf(f, "Tri Bulle: %.6f s\n", t1);
        fprintf(f, "Tri Bulle Opt: %.6f s\n", t2);
        fprintf(f, "Tri par Tas: %.6f s\n", t3);
        fprintf(f, "Tri rapide: %.6f s\n", t4);
        fprintf(f, "Tri par Distribution: %.6f s\n", t5);
         fprintf(f, "Tri Gnome: %.6f s\n", t6);
        fprintf(f, "\n");

        free(T);
    }

    fclose(f);
    return 0;
}
