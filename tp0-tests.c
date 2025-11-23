// TP0 - Moncef Kameli - SII Groupe 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *out = fopen("Test-3.txt", "w");
    if (!out) return 1;

    srand(time(NULL));  // pour générer des nombres aléatoires

    int digits_list[] = {3, 6, 9, 12};   // les tailles demandées
    int count_per_group = 10;            // 10 nombres pour chaque taille

    for (int k = 0; k < 4; k++) {
        int digits = digits_list[k];

        long long min = 1;
        for (int i = 1; i < digits; i++)  // construit 10^(digits-1)
            min *= 10;

        long long max = min * 10 - 1;     // ex: 999 pour 3 chiffres

        for (int j = 0; j < count_per_group; j++) {
            long long num = min + rand() % (max - min + 1);
            fprintf(out, "%lld\n", num);
        }
    }

    fclose(out);
    return 0;
}