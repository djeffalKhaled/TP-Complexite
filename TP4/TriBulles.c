#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


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

double measure_temp(int* T, int n, int repeats, void (*algo)(int*, int)) {
    double total = 0;
    int posI, posJ;
    for (int r = 0; r < repeats; r++) {
        // pour ne pas changer les valeurs de T
        int* copy = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) copy[i] = T[i];

        clock_t start = clock();
        algo(copy, n);
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total / repeats;
}

int main() {
    printf("TRI BOULE\n");
    srand(time(NULL));
    int n;
    printf("Taille du tableau? ");
    scanf("%d", &n);
    int* T = malloc(sizeof(int) * n);

    remplireValeursRand(T, n);
    //afficher(T, n);

    double temp = measure_temp(T, n, 200, tribulle);
    printf("T = %lf s\n", temp);

    temp = measure_temp(T, n, 200, tribulleopt);
    printf("T = %lf s\n", temp);

    return 0;
}