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
        estPremierA1(N); // l'algorithme a mesuré
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total / repeats;
}



// calcule temp d'executions a partir les jeux de donnees
int main() {
    long nombres[] = {1000003,2000003,4000037,8000009,16000057, 32000011,64000031,128000003,256000001,512000009,1024000009,2048000011};;
    int size = 11;

    for (int i = 0; i < size; i++) {
        long N = nombres[i];

        double temp = measure_prime_time(N, 1); 

        printf("N = %ld - T = %f\n", N, temp);
    }
    return 0;
}

