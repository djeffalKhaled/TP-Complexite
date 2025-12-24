#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void permuter(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

void afficher(int* T, int n) {
    printf("T = {");
    for (int i = 0; i < n; i++) {
        printf("%d", T[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
}

double measure_temp(int* T, int n, int repeats, void (*algo)(int*, int)) {
    double total = 0;
    for (int r = 0; r < repeats; r++) {
        int* copy = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) copy[i] = T[i];

        clock_t start = clock();
        algo(copy, n);
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;

        free(copy);
    }
    return total / repeats;
}

int main() {
    printf("TRI PAR TAS\n");
    srand(time(NULL));
    int n;
    printf("Taille du tableau? ");
    scanf("%d", &n);

    int* T = malloc(sizeof(int) * n);
    remplireValeursRand(T, n);

    double temp = measure_temp(T, n, 200, triParTas);
    printf("T = %lf s\n", temp);

    free(T);
    return 0;
}
