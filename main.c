/*

Integrantes:

    - Huaman Ramirez Ana Cristina           20200179
    - Perez Sotacuro Esthefanie Gerarda     20200232
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordInfo;

int main() {
    int numWords = 0;
    WordInfo words[MAX_WORDS] = {0};
    int totalDocuments = 0;


    // Abre el archivo de texto
    FILE *file = fopen("D:\\test.txt", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Lee el contenido del archivo palabra por palabra
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        // Convierte la palabra a minúsculas
        for (int i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }

        // Busca la palabra en la lista de palabras
        int i;
        for (i = 0; i < numWords; i++) {
            if (strcmp(words[i].word, word) == 0) {
                break;
            }
        }

        // Si la palabra no está en la lista, agrégala
        if (i == numWords) {
            strncpy(words[numWords].word, word, MAX_WORD_LENGTH);
            words[numWords].count = 1;
            numWords++;
        } else {
            words[i].count++;
        }
	totalDocuments++;
    }

    // Cierra el archivo
    fclose(file);

    // Crea el vector de características
    double vectorCaracteristicas[MAX_WORDS];
    for (int i = 0; i < numWords; i++) {
        double tf = (double)words[i].count / totalDocuments;
        double idf = log((double)numWords / (i + 1)); // i + 1 porque los índices empiezan desde 0
        double tdif= tf * idf;
        vectorCaracteristicas[i] = tdif;
    }

    // Imprime las palabras y sus conteos junto con el TDIF
    for (int i = 0; i < numWords; i++) {
        printf("%s: %d (tdif: %.2f)\n", words[i].word, words[i].count, vectorCaracteristicas[i]);
    }

    // Imprime el vector de características
    printf("\nVector de Características:\n");
    for (int i = 0; i < numWords; i++) {
        printf("%.2f ", vectorCaracteristicas[i]);
    }
    printf("\n");

    return 0;
}