// TP2 - Moncef Kameli 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPEAT 10000  // nombre de répétitions pour augmenter le temps mesuré

int rechElets_TabNonTries(int T[], int n, int x){
    for(int i = 0; i < n; i++){
        if(T[i] == x) return 1;
    }
    return 0;
}

int rechElets_TabTries(int T[], int n, int x){
    for(int i = 0; i < n; i++){
        if(T[i] == x) return 1;
        if(T[i] > x) return 0;
    }
    return 0;
}

int rechElets_Dicho(int T[], int n, int x){
    int L = 0, R = n - 1;
    while(L <= R){
        int m = (L + R) / 2;
        if(T[m] == x) return 1;
        if(T[m] < x) L = m + 1;
        else R = m - 1;
    }
    return 0;
}

void generateRandom(int T[], int n){
    for(int i = 0; i < n; i++)
        T[i] = rand() % (2*n);
}

void generateSorted(int T[], int n){
    for(int i = 0; i < n; i++)
        T[i] = i;
}

double measure_time(int (*f)(int*,int,int), int T[], int n, int x){
    clock_t start = clock();

    for(int k = 0; k < REPEAT; k++)
        f(T, n, x);

    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC) / REPEAT;
}

int main(){
    srand(time(NULL));

    int sizes[] = {100000,200000,400000,600000,800000,
                   1000000,1200000,1400000,1600000,1800000};
    int nb = 10;

    printf("n\tNonTrie_M\tNonTrie_P\tTrie_M\tTrie_P\tDicho_M\tDicho_P\n");

    for(int s = 0; s < nb; s++){
        int n = sizes[s];
        int *T = malloc(n * sizeof(int));

        generateRandom(T, n);
        double t1m = measure_time(rechElets_TabNonTries, T, n, T[0]);
        double t1p = measure_time(rechElets_TabNonTries, T, n, -1);

        generateSorted(T, n);
        double t2m = measure_time(rechElets_TabTries, T, n, T[0]);
        double t2p = measure_time(rechElets_TabTries, T, n, -1);

        double t3m = measure_time(rechElets_Dicho, T, n, T[0]);
        double t3p = measure_time(rechElets_Dicho, T, n, -1);

        printf("%d\t%.8lf\t%.8lf\t%.8lf\t%.8lf\t%.8lf\t%.8lf\n",
               n, t1m, t1p, t2m, t2p, t3m, t3p);

        free(T);
    }

    return 0;
}
