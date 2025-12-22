// TP2 - Moncef Kameli 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

/* Paramètres de mesure */
#define REPEAT_TIME 200   
#define TRIALS 5          
#define MAX_SIZES 10

/* ------------------- Méthode A (naïve) ------------------- */
void MaxEtMinA(int T[], int n, int *pmin, int *pmax, long *cmp){
    if(n <= 0){
        if(pmin) *pmin = 0;
        if(pmax) *pmax = 0;
        return;
    }
    int min = T[0], max = T[0];
    for(int i = 1; i < n; i++){
        (*cmp)++;               /* compare T[i] < min ? */
        if(T[i] < min) min = T[i];
        (*cmp)++;               /* compare T[i] > max ? */
        if(T[i] > max) max = T[i];
    }
    if(pmin) *pmin = min;
    if(pmax) *pmax = max;
}

void MaxEtMinB(int T[], int n, int *pmin, int *pmax, long *cmp){
    if(n <= 0){
        if(pmin) *pmin = 0;
        if(pmax) *pmax = 0;
        return;
    }

    int last_unpaired = -1;
    for(int i = 0; i + 1 < n; i += 2){
        (*cmp)++; 
        if(T[i] < T[i+1]){
            int tmp = T[i];
            T[i] = T[i+1];
            T[i+1] = tmp;
        }
        
    }
    if(n % 2 == 1) last_unpaired = n - 1;

    int maxv = T[0];
    for(int i = 2; i < n; i += 2){
        (*cmp)++; /* comparaison pour max */
        if(T[i] > maxv) maxv = T[i];
    }

    int minv;
    if(n >= 2){
        minv = T[1];
        for(int i = 3; i < n; i += 2){
            (*cmp)++; /* comparaison pour min */
            if(T[i] < minv) minv = T[i];
        }
    } else {
        minv = T[0];
    }

    if(last_unpaired != -1){
        int idx = last_unpaired;
        if(idx % 2 == 0){
            (*cmp)++;
            if(T[idx] > maxv) maxv = T[idx];
        } else {
            (*cmp)++;
            if(T[idx] < minv) minv = T[idx];
        }
    }

    if(pmin) *pmin = minv;
    if(pmax) *pmax = maxv;
}


void generateRandom(int T[], int n){
    for(int i = 0; i < n; i++) T[i] = rand() % (2*n + 1);
}
void generateSorted(int T[], int n){
    for(int i = 0; i < n; i++) T[i] = i;
}
void generateReverseSorted(int T[], int n){
    for(int i = 0; i < n; i++) T[i] = n - 1 - i;
}

double measure_time_void(void (*f)(int*,int,int*,int*,long*), int T[], int n){
    clock_t start = clock();
    int minv, maxv;
    long cmp;
    for(int k = 0; k < REPEAT_TIME; k++){
        cmp = 0;
        f(T, n, &minv, &maxv, &cmp);
    }
    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC) / REPEAT_TIME;
}

/* ------------------- Main ------------------- */
int main(){
    srand((unsigned int)time(NULL));

    int sizes[MAX_SIZES] = {100000,200000,400000,600000,800000,1000000,1200000,1400000,1600000,1800000};
    int nb_sizes = 10;

  
    printf("# Partie B - Max&Min (A vs B pairwise)\n");
    printf("# REPEAT_TIME=%d TRIALS=%d\n", REPEAT_TIME, TRIALS);
    printf("n\ttype\tNaive_Cmp\tPair_Cmp\tNaive_Time(s)\tPair_Time(s)\n");
    fflush(stdout); 

    for(int si = 0; si < nb_sizes; si++){
        int n = sizes[si];
        int *T = (int*)malloc(sizeof(int)*n);
        if(!T){
            fprintf(stderr, "malloc failed n=%d\n", n);
            return 1;
        }

      
        double sum_cmp_naive = 0.0, sum_cmp_pair = 0.0;
        double sum_time_naive = 0.0, sum_time_pair = 0.0;
        for(int t = 0; t < TRIALS; t++){
            generateRandom(T, n);

            
            int *copy = (int*)malloc(sizeof(int)*n);
            if(!copy){
                fprintf(stderr, "malloc(copy) failed n=%d\n", n);
                free(T);
                return 1;
            }
            memcpy(copy, T, sizeof(int)*n);

            long cmpA = 0, cmpB = 0;
            int minA=0, maxA=0, minB=0, maxB=0;

            MaxEtMinA(T, n, &minA, &maxA, &cmpA);
            MaxEtMinB(copy, n, &minB, &maxB, &cmpB);

            sum_cmp_naive += (double)cmpA;
            sum_cmp_pair += (double)cmpB;

            
            memcpy(copy, T, sizeof(int)*n);
            double ta = measure_time_void(MaxEtMinA, T, n);
            double tb = measure_time_void(MaxEtMinB, copy, n);
            sum_time_naive += ta;
            sum_time_pair += tb;

            free(copy);
        }
        printf("%d\trand\t%.2f\t%.2f\t%.8f\t%.8f\n",
               n,
               sum_cmp_naive / TRIALS,
               sum_cmp_pair / TRIALS,
               sum_time_naive / TRIALS,
               sum_time_pair / TRIALS);

       
        sum_cmp_naive = sum_cmp_pair = 0.0;
        sum_time_naive = sum_time_pair = 0.0;
        for(int t = 0; t < TRIALS; t++){
            generateSorted(T, n);

            int *copy = (int*)malloc(sizeof(int)*n);
            if(!copy){ fprintf(stderr, "malloc copy failed\n"); free(T); return 1; }
            memcpy(copy, T, sizeof(int)*n);

            long cmpA = 0, cmpB = 0;
            int minA=0, maxA=0, minB=0, maxB=0;
            MaxEtMinA(T, n, &minA, &maxA, &cmpA);
            MaxEtMinB(copy, n, &minB, &maxB, &cmpB);
            sum_cmp_naive += cmpA;
            sum_cmp_pair += cmpB;

            memcpy(copy, T, sizeof(int)*n);
            double ta = measure_time_void(MaxEtMinA, T, n);
            double tb = measure_time_void(MaxEtMinB, copy, n);
            sum_time_naive += ta;
            sum_time_pair += tb;

            free(copy);
        }
        printf("%d\tsorted\t%.2f\t%.2f\t%.8f\t%.8f\n",
               n,
               sum_cmp_naive / TRIALS,
               sum_cmp_pair / TRIALS,
               sum_time_naive / TRIALS,
               sum_time_pair / TRIALS);

        
        sum_cmp_naive = sum_cmp_pair = 0.0;
        sum_time_naive = sum_time_pair = 0.0;
        for(int t = 0; t < TRIALS; t++){
            generateReverseSorted(T, n);

            int *copy = (int*)malloc(sizeof(int)*n);
            if(!copy){ fprintf(stderr, "malloc copy failed\n"); free(T); return 1; }
            memcpy(copy, T, sizeof(int)*n);

            long cmpA = 0, cmpB = 0;
            int minA=0, maxA=0, minB=0, maxB=0;
            MaxEtMinA(T, n, &minA, &maxA, &cmpA);
            MaxEtMinB(copy, n, &minB, &maxB, &cmpB);
            sum_cmp_naive += cmpA;
            sum_cmp_pair += cmpB;

            memcpy(copy, T, sizeof(int)*n);
            double ta = measure_time_void(MaxEtMinA, T, n);
            double tb = measure_time_void(MaxEtMinB, copy, n);
            sum_time_naive += ta;
            sum_time_pair += tb;

            free(copy);
        }
        printf("%d\trev_sorted\t%.2f\t%.2f\t%.8f\t%.8f\n",
               n,
               sum_cmp_naive / TRIALS,
               sum_cmp_pair / TRIALS,
               sum_time_naive / TRIALS,
               sum_time_pair / TRIALS);

        free(T);
    }

    return 0;
}
