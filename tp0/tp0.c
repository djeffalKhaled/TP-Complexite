// TP0 : DJEFFAL Khaled
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int choisirRandom(int valeurmax) {
    return rand() % valeurmax;
}
void libererChaine(char **chaine, int max) {
    for (int i = 0; i < max; i++) {
        free(chaine[i]);
    }
    free(chaine);
}

int main() {

    // ---------------- PREPARATION DES DONNES --------------------
    FILE* file = fopen("primes10.txt", "r");

    if (file) {
        printf("Le fichier exist\n");
    } else {
        printf("Le fichier n'exist pas, assuré que primes10.txt ce trouve avec le projet\n");
        return 1;
    }

    char text[100]; 

    // On prendre 10000000 element pour minimiser l'attend, et on lire le fichier 
    // et mettre chaque valeur dans le tableau fileElements
    int maxLines = 10000000;
    int readLines = 0;  
    char **fileElements = malloc(maxLines * sizeof(char*));
    for (int i = 0; i < maxLines; i++) {
        fileElements[i] = malloc(100 * sizeof(char)); 
    }

    while(fgets(text, 100, file) && readLines < maxLines) {
        text[strcspn(text, "\n")] = 0; 
        strcpy(fileElements[readLines], text);
        printf("\riteration %d jusqu'a %d", readLines + 1, maxLines);
        fflush(stdout);    
        readLines++;
    }
    printf("\n \n \n");



    // ---------------- QUESTION 1 --------------------

    // On choisir 100 elements random et le mettre dans le tableau random100 
    srand(time(NULL));
    char **random100 = malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++) {
        random100[i] = malloc(100 * sizeof(char)); 
    }

    for (int i = 0; i < 100; i++) {
        int element = choisirRandom(readLines);
        strcpy(random100[i], fileElements[element]);
    }

    printf("\nELEMENTS DE RANDOM100 : ---------\n");

    for (int i = 0; i < 100; i++) {
       printf("%s \n", random100[i]);
    }

    // On transform le tableau random100 vers un fichier pour avoir le jeu de données :
    FILE *random100File = fopen("random100.txt", "w");
    if (!random100File) {
        printf("Probleme de creation de fichier\n");
    } else {
        for (int i = 0; i < 100; i++) {
            fprintf(random100File, "%s\n", random100[i]); 
        }
        fclose(random100File);
        printf("Fichier qui contient 100 nombre aletoires primaire est cree avec le nom random100.txt\n");
    }

    // ---------------- QUESTION 2 --------------------

    // On choisir 1000 elements random et le mettre dans le tableau random100 
    char **random1000 = malloc(1000 * sizeof(char*));
    for (int i = 0; i < 1000; i++) {
        random1000[i] = malloc(100 * sizeof(char)); 
    }

    for (int i = 0; i < 1000; i++) {
        int element = choisirRandom(readLines);
        strcpy(random1000[i], fileElements[element]);
    }

    printf("\nELEMENTS DE RANDOM1000 : ---------\n");

    for (int i = 0; i < 1000; i++) {
       printf("%s \n", random1000[i]);
    }


    // On transform le tableau random1000 vers un fichier pour avoir le jeu de données :
    FILE *random1000File = fopen("random1000.txt", "w");
    if (!random1000File) {
        printf("Probleme de creation de fichier\n");
    } else {
        for (int i = 0; i < 1000; i++) {
            fprintf(random1000File, "%s\n", random1000[i]); 
        }
        fclose(random1000File);
        printf("Fichiers qui contient 1000 nombre aletoires primaire est cree avec le nom random100.txt\n");
    }



    // ---------------- QUESTION 3 --------------------
    // Le 3eme jeu, nomme Test-1 contenant un échantillon de 100 nombres premiers tirés aléatoirement dans l’intervalle [1000, 1000000]
    char **test1 = malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++) {
        test1[i] = malloc(100 * sizeof(char));
    }

    for (int i = 0; i < 100; i++) {
        int element;
        // On choisi l'element en tant que le nombre primaire est entre 1000 et 1000000.
        do {
            element = choisirRandom(readLines - 1);
        } while (atoi(fileElements[element]) < 1000 || atoi(fileElements[element]) > 1000000); 
        strcpy(test1[i], fileElements[element]);
    }

    printf("\nELEMENTS DE TEST-1 : ---------\n");
    for (int i = 0; i < 100; i++) {
        printf("%s\n", test1[i]);
    }

    FILE *test1File = fopen("Test-1.txt", "w");
    if (!test1File) {
        printf("Probleme de creation de fichier\n");
    } else {
        for (int i = 0; i < 100; i++) {
            fprintf(test1File, "%s\n", test1[i]);
        }
        fclose(test1File);
        printf("Fichier qui contient 100 nombre aletoires primaire dans l'intervalle 100 et 1000000 est cree avec le nom Test-1.txt\n");
    }



    // ---------------- QUESTION 4 --------------------
    // Il faut prendre 10 nombre premier a n chiffres tq n > 0
    char **test2 = malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++) {
        test2[i] = malloc(100 * sizeof(char));
    }

    int count = 0;
    for (int chiffres = 2; chiffres <= 12; chiffres++) {
        int min = 1;
        for (int j = 1; j < chiffres; j++) min *= 10;
        int max = min * 10 - 1;
        int validCount = 0;
        int *validIndices = malloc(readLines * sizeof(int));
        for (int i = 0; i < readLines; i++) {
            int value = atoi(fileElements[i]);
            if (value >= min && value <= max) {
                validIndices[validCount] = i;
                validCount++;
            }
        }

        int toSelect = validCount < 10 ? validCount : 10;

        for (int i = 0; i < toSelect; i++) {
            int randIndex = choisirRandom(validCount - 1);
            strcpy(test2[count], fileElements[validIndices[randIndex]]);
            validIndices[randIndex] = validIndices[validCount - 1];
            validCount--;
            count++;
        }
        free(validIndices);
    }

    printf("ELEMENTS DE TEST-2 : ---------\n");
    for (int i = 0; i < 100; i++) {
        printf("%s\n", test2[i]);
    }

    FILE *test2File = fopen("Test-2.txt", "w");
    if (!test2File) {
        printf("Problème de création de fichier\n");
    } else {
        for (int i = 0; i < 70; i++) {
            fprintf(test2File, "%s\n", test2[i]);
        }
        fclose(test2File);
        printf("Fichier qui contient 100 nombre aletoires primaire organiser en fonction des chiffres est cree avec le nom Test-2.txt\n\n");
    }


    fclose(file);
    libererChaine(fileElements, readLines);
    libererChaine(random100, 100);
    return 0;
}