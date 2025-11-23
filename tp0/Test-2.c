// TP0 - Moncef Kameli - SII Groupe 1 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *f = fopen("primes10.txt", "r");
    if (!f) return 1;

    long long *p = malloc(1000 * sizeof(long long));
    long long n = 0, cap = 1000, x;

    while (fscanf(f, "%lld", &x) == 1) {
        if (n == cap) {
            cap *= 2;
            p = realloc(p, cap * sizeof(long long));
        }
        p[n++] = x;
    }
    fclose(f);

    srand(time(NULL));

    FILE *out = fopen("Test-2.txt", "w");
    for (int digits = 3; digits <= 6; digits++) {
        long long min = 1;
        for (int i = 1; i < digits; i++) min *= 10;
        long long max = min * 10 - 1;

        int count = 0;
        for (long long i = n - 1; i >= 0 && count < 10; i--) {
            if (p[i] >= min && p[i] <= max) {
                fprintf(out, "%lld\n", p[i]);
                count++;
            }
        }
    }
    fclose(out);
    free(p);
    return 0;
}
