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
    for (long long i = n - 1; i > 0; i--) {
        long long j = rand() % (i + 1), t = p[i];
        p[i] = p[j]; p[j] = t;
    }

    FILE *out = fopen("Random1000.txt", "w");
    for (int i = 0; i < 1000; i++) fprintf(out, "%lld\n", p[i]);
    fclose(out);

    free(p);
    return 0;
}

