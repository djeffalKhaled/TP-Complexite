#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void permuter(int* T1, int* T2) {
    int temp = *T1;
    *T1 = *T2;
    *T2 = temp;
}

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

void remplireValeursRand(int* T, int n) {
    for (int i = 0; i < n; i++) {
        T[i] = rand() % 1000000000;
    }
}

void afficher(int * T, int n) {
    printf("T = {");
    for (int i = 0; i < n; i++) {
        if (i == (n-1)) {
            printf("%d", T[i]);
            break;
        }
        printf("%d,", T[i]);
    }
    printf("}\n");
}

double measure_temp(int* T, int n, int repeats, void (*algo)(int*, int, int)) {
    double total = 0;
    for (int r = 0; r < repeats; r++) {
        int* copy = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) copy[i] = T[i];

        clock_t start = clock();
        algo(copy, 0, n - 1); 
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;

        free(copy);
    }
    return total / repeats;
}


int main() {
    printf("TRI RAPIDE\n");
    srand(time(NULL));
    int n;
    printf("Taille du tableau? ");
    scanf("%d", &n);
    int* T = malloc(sizeof(int) * n);

    remplireValeursRand(T, n);
    //afficher(T, n);

    double temp = measure_temp(T, n, 200, triRapide);
    printf("T = %lf s\n", temp);

    free(T);
    return 0;
}