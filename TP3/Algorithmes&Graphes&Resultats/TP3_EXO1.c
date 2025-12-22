#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random(int min, int max) {
    return min + rand() % (max - min + 1);
}

double** allouer_matrice(int n, int m) {
    double** M = (double**)malloc(sizeof(double*) * n); // allocation ligne
    for (int i = 0; i < n; i++) {
        M[i] = (double*)malloc(sizeof(double) * m); // allocation col
    }
    printf("Matrice Alloue\n");
    return M;
}

void remplire_matrice_random(double** M, int n, int m) {
    int total = n * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            M[i][j] = random(0, 108);
        }
    }
}

void afficher_matrice(double** M, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%g ", M[i][j]);
        }
        printf("\n");
    }
}

void liberer_matrice(double** M, int n) {
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);
}


int main() {
    srand(time(NULL));
    int n, m, p;
    printf("n = ? \n"); scanf("%d", &n);
    printf("m = ? \n"); scanf("%d", &m);
    printf("p = ? \n"); scanf("%d", &p);

    // allocation et preparation des matrices (avec des valeurs aléatoires)
    double **A = allouer_matrice(n, m);
    double **B = allouer_matrice(m, p);
    double **C = allouer_matrice(n, p);
    remplire_matrice_random(A, n, m);
    remplire_matrice_random(B, n, p);

    // initilisation de C a zero
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0.0;
        }
    }

    // Multiplication Matricielle : C = A x B
    // Trois boucle imbriquées ==> complexite d'ordre o(n^3)
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            double aik = A[i][k]; 
            for (int j = 0; j < n; j++) {
                C[i][j] += aik * B[k][j];
            }
        }
    }

    // Affichage des matrices
    printf("\nMatrix A:\n"); afficher_matrice(A, n, m);
    printf("\nMatrix B:\n"); afficher_matrice(B, m, p);
    printf("\nMatrix C = A * B:\n"); afficher_matrice(C, n, p);

    liberer_matrice(A, n); liberer_matrice(B, m); liberer_matrice(C, n);
    return 0;
}
