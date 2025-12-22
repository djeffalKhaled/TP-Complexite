#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

bool estPremierA1(long N) {
    if (N == 0 || N == 1) { return false; }
    
    for (long i = 2; i <= N-1; i++) { // (n-1)-(2)+1 units   from (b-a)+1 tq a < b
        if (N % i == 0) { 
            return false;
        }
    } 
    return true; 
}
// Complexité = (n-2)  ---> o(n)

bool estPremierA2(long N) {
    if (N == 0 || N == 1) { return false; }
    
    for (long i = 2; i <= N/2; i++) { // (n/2)-(2)+1 units = (n/2)-1
        if (N % i == 0) { 
            return false;
        }
    } 
    return true; 
}
// o(n/2) --> o(n)

bool estPremierA3(long N) {
    if (N <= 1) return false;
    for (long i = 2; i <= sqrt(N); i++) {
        if (N % i == 0) return false;
    }
    return true;
}
// o(sqrt(n))



bool estPremierA4(long N) {
    if (N == 2) return true;
    if (N < 2 || N % 2 == 0) return false;

    for (long i = 3; i <= sqrt(N); i+=2) { // += 2 pour assurer le test juste pour des nombres impaires (3, 5, 7, ...)
        if (N % i == 0) {
            return false;
        }
    }
    return true;
}
// o(sqrt(n))

double measure_prime_time(long N, int repeats, bool (*algo)(long)) {
    double total = 0;
    for (int r = 0; r < repeats; r++) {
        clock_t start = clock();
        algo(N);
        clock_t end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total / repeats;
}


int main() {
    FILE* file = fopen("Test-3.txt", "r");
    if (!file) {
        printf("File doesn't exist!\n"); return 1;
    }

    long* nums = malloc(sizeof(long) * 100);
    char buffer[100];
    int size = 0;

    while (fgets(buffer, 100, file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        nums[size++] = atol(buffer);
    }
    fclose(file);

    bool (*algos[4])(long) = { estPremierA1, estPremierA2, estPremierA3, estPremierA4 };
    const char* names[4]   = { "A1", "A2", "A3", "A4" };

    for (int a = 0; a < 4; a++) {
        char f1[256], f2[256];
        sprintf(f1, "results/%s_results.txt", names[a]);
        sprintf(f2, "results/%s_detailed_results.txt", names[a]);

        FILE* r1 = fopen(f1, "w");
        FILE* r2 = fopen(f2, "w");
        if (!r1 || !r2) return 1;

        for (int i = 0; i < size; i++) {
            long N = nums[i];
            double t = measure_prime_time(N, 50, algos[a]);

            //printf("%s | N = %ld - T = %f\n", names[a], N, t);
            //fprintf(r1, "%ld %f\n", N, t);
            //fprintf(r2, "%s | N = %ld - T = %f\n", names[a], N, t);

            // juste pour test-3
            bool premier = algos[a](N);
            printf("%s | N = %ld - T = %f - Premier? = %d\n", names[a], N, t, premier);
            fprintf(r1, "%ld %f %d\n", N, t, premier);
            fprintf(r2, "%s | N = %ld - T = %f - Premier? = %d\n", names[a], N, t, premier);
        }

        fclose(r1);
        fclose(r2);
    }

    free(nums);
    return 0;
}
