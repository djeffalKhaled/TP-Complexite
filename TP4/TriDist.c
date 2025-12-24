#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int cle(int x, int i) {
    int div = 1;
    for(int j = 0; j < i; j++) div *= 10;
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

void remplireValeursRand(int* T, int n) {
    for (int i = 0; i < n; i++)
        T[i] = rand() % 1000000000;
}

void afficher(int* T, int n) {
    printf("T = {");
    for (int i = 0; i < n; i++) {
        printf("%d", T[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
}

double measure_temp(int* T, int n, int repeats, void (*algo)(int*, int, int), int k) {
    double total = 0;
    for (int r = 0; r < repeats; r++) {
        int* copy = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) copy[i] = T[i];

        clock_t start = clock();
        for (int i = 0; i < k; i++)
            algo(copy, n, i);
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;

        free(copy);
    }
    return total / repeats;
}

int main() {
    srand(time(NULL));
    int n;
    printf("Taille du tableau? ");
    scanf("%d", &n);

    int* T = malloc(sizeof(int) * n);
    remplireValeursRand(T, n);

    int k = 9;
    double temp = measure_temp(T, n, 200, triAux, k);

    printf("T = %lf s\n", temp);
    
    free(T);
    return 0;
}
