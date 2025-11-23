#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

bool estPremierA1(int N) {
    if (N == 0 || N == 1) { return false; }
    
    for (int i = 2; i <= N-1; i++) { // (n-1)-(2)+1 units   from (b-a)+1 tq a < b
        if (N % i == 0) { 
            return false;
        }
    } 
    return true; 
}
// Complexité = (n-2)  ---> o(n)

bool estPremierA2(int N) {
    if (N == 0 || N == 1) { return false; }
    
    for (int i = 2; i <= N/2; i++) { // (n/2)-(2)+1 units = (n/2)-1
        if (N % i == 0) { 
            return false;
        }
    } 
    return true; 
}
// o(n/2) --> o(n)

bool estPremierA3(int N) {
    if (N <= 1) return false;
    for (int i = 2; i <= sqrt(N); i++) {
        if (N % i == 0) return false;
    }
    return true;
}
// o(sqrt(n))



bool estPremierA4(int N) {
    if (N == 2) return true;
    if (N < 2 || N % 2 == 0) return false;

    for (int i = 3; i <= sqrt(N); i+=2) { // += 2 pour assurer le test juste pour des nombres impaires (3, 5, 7, ...)
        if (N % i == 0) {
            return false;
        }
    }
    return true;
}
// o(sqrt(n))

// calcule de temp d'exec avec une repetition (pour assuré un calcule precise)
double measure_prime_time(long N, int repeats) {
    double total = 0;
    for(int r = 0; r < repeats; r++) {
        clock_t start = clock();
        estPremierA2(N); // l'algorithme a mesuré
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total / repeats;
}



// calcule temp d'executions a partir les jeux de donnees
int main() {
    FILE* file = fopen("random100.txt", "r");
    if (!file) return 1;
    char text[100];
    long* nombresFichier = (long*) malloc(sizeof(long) * 100);
    int i = 0;
    while(fgets(text, 100, file)) {
        text[strcspn(text, "\n")] = 0; 
        nombresFichier[i] =  atol(text);
        i++;
    }
    int size = i;

    FILE* results = fopen("results/A2_results.txt", "w");
    FILE* detailedResults = fopen("results/A2_detailed_results.txt", "w");
    if (!results || !detailedResults) return 1;

    for (int i = 0; i < size; i++) {
        long N = nombresFichier[i];

        double temp = measure_prime_time(N, 150); 

        printf("N = %ld - T = %f\n", N, temp);
        
        fprintf(results, "%ld %f\n", N, temp);
        fprintf(detailedResults, "N = %ld - T = %f\n", N, temp);
    }

    free(nombresFichier);
    fclose(file); fclose(results); fclose(detailedResults);
    return 0;
}

