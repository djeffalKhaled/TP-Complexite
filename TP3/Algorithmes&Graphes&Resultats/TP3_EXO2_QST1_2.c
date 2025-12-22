#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

double measure_temp(int** A, int n, int m, int** B, int np, int mp, int repeats, bool (*algo)(int**, int, int, int**, int, int, int*, int*)) {
    double total = 0;
    int posI, posJ;
    for (int r = 0; r < repeats; r++) {
        clock_t start = clock();
        algo(A, n, m, B, np, mp, &posI, &posJ);
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total / repeats;
}


bool sous_matrice(int** A, int n, int m, int**B, int np, int mp, int* posI, int* posJ) {
    for (int i = 0; i <= n - np; i++) {
        for (int j = 0; j <= m - mp; j++) {
            // parcour A, chaque element parcourir B et la comparé
            bool sous_matrice = true; 
            for (int k = 0; k < np && sous_matrice; k++) {
                for (int l = 0; l < mp; l++) {
                    // offset A par k et l 
                    if (A[i + k][j + l] != B[k][l]) {
                        sous_matrice = false;
                        break;
                    }
                }
            }

            if (sous_matrice) {
                *posI = i;
                *posJ = j;
                return true;
            }
        }
    }
    return false;
}

int recherche_binaire(int* arr, int m, int val) {
    int left = 0, right = m - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == val) return mid;
        else if (arr[mid] < val) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

bool sous_matrice2(int** A, int n, int m, int** B, int np, int mp, int *posI, int *posJ) {
    for (int i = 0; i <= n - np; i++) {
        int gauche = 0, droite = m - mp;
        while (gauche <= droite) {
            int mid = (gauche + droite) / 2;
            if (A[i][mid] < B[0][0]) gauche = mid + 1;
            else droite = mid - 1;
        }
        for (int j = gauche; j <= m - mp; j++) {
            if (A[i][j] != B[0][0]) break;
            bool sous_matrice = true;
            for (int k = 0; k < np && sous_matrice; k++) {
                for (int l = 0; l < mp; l++) {
                    if (A[i + k][j + l] != B[k][l]) {
                        sous_matrice = false;
                        break;
                    }
                }
            }
            if (sous_matrice) {
                *posI = i;
                *posJ = j;
                return true;
            }
        }
    }
    return false;
}



int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

int** allouer_matrice(int n, int m) {
    int** M = (int**)malloc(sizeof(int*) * n); // allocation ligne
    for (int i = 0; i < n; i++) {
        M[i] = (int*)malloc(sizeof(int) * m); // allocation col
    }
    printf("Matrice Alloue\n");
    return M;
}

void afficher_matrice(int** M, int n, int m) {
    printf("MATRICE : \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%4d ", M[i][j]);
        }
        printf("\n");
    }
}

void remplire_matrice_random(int** M, int n, int m) {
    int total = n * m;
    int cmpt = 0; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            M[i][j] = random(0, 108);

            cmpt++;
            if (cmpt % (total / 100) == 0) {
                printf("\rRemplissage: %d%%", cmpt * 100 / total);
                fflush(stdout);
            }
        }
    }
    printf("\n");
}

void trier_matrice(int** M, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            for (int k = 0; k < m - j - 1; k++) {
                if (M[i][k] > M[i][k + 1]) {
                    int temp = M[i][k];
                    M[i][k] = M[i][k + 1];
                    M[i][k + 1] = temp;
                }
            }
        }
    }
}

void force_sous_matrice(int** A, int n, int m, int** B, int np, int mp) {
    int i0 = rand() % (n - np + 1);
    int j0 = rand() % (m - mp + 1);
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < mp; j++) {
            B[i][j] = A[i0 + i][j0 + j];
        }
    }
}

void liberer_matrice(int** M, int n) {
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);
}


int main() {
    // preparation des matrices A et B
    srand(time(NULL));
    int n = 500, m = 500; 
    int np = 50, mp = 50;   
    int** A = allouer_matrice(n, m); 
    int** B = allouer_matrice(np, mp); 
    remplire_matrice_random(A, n, m);
    remplire_matrice_random(B, np, mp);
    //afficher_matrice(A, n, m);
    //afficher_matrice(B, np, mp);

    // -------------------- QUESTION 1 -----------------
    printf("\nCAS B N'EST PAS SOUS MATRICE :\n"); 
    int posI, posJ;
    bool sous_mat = sous_matrice(A, n, m, B, np, mp, &posI, &posJ);
    printf("Sous matrice? %d\n", sous_mat);
    if (sous_mat) printf("Position: (%d, %d)\n", posI, posJ);

    double t1 = measure_temp(A, n, m, B, np, mp, 50, sous_matrice);
    printf("Temps moyen sous_matrice: %f secondes\n", t1);

    printf("\nCAS B EST SOUS MATRICE :\n");
    force_sous_matrice(A, n, m, B, np, mp);
    sous_mat = sous_matrice(A, n, m, B, np, mp, &posI, &posJ);
    printf("Sous matrice? %d\n", sous_mat);
    if (sous_mat) printf("Position: (%d, %d)\n", posI, posJ);

    double t2 = measure_temp(A, n, m, B, np, mp, 100, sous_matrice);
    printf("Temps moyen sous_matrice: %f secondes\n", t2); 



    // ------------------- QUESTION 2 -----------------
    printf("\n-------------QUESTION 2----------\n");
    printf("\nCAS B N'EST PAS SOUS MATRICE :\n");
    trier_matrice(A, n, m);
    trier_matrice(B, np, mp);

    sous_mat = sous_matrice2(A, n, m, B, np, mp, &posI, &posJ);
    printf("Sous matrice? %d\n", sous_mat);
    if (sous_mat) printf("Position: (%d, %d)\n", posI, posJ);

    double t3 = measure_temp(A, n, m, B, np, mp, 100, sous_matrice2);
    printf("Temps moyen sous_matrice2: %f secondes\n", t3);

    printf("\nCAS B EST SOUS MATRICE :\n");
    force_sous_matrice(A, n, m, B, np, mp);
    sous_mat = sous_matrice2(A, n, m, B, np, mp, &posI, &posJ);
    printf("Sous matrice? %d\n", sous_mat);
    if (sous_mat) printf("Position: (%d, %d)\n", posI, posJ);

    double t4 = measure_temp(A, n, m, B, np, mp, 150, sous_matrice2);
    printf("Temps moyen sous_matrice: %f secondes\n", t4); 

    liberer_matrice(A, n);
    liberer_matrice(B, np);
    return 0;
}
