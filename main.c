#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "./include/utils.h"
#include "./include/lexer.h"
#include "./include/sasm.h"
#include "./include/parser.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Utilisation : %s [options] fichier\n", argv[0]);
        return 1;
    }

    const char *output = "a.out";  // Fichier de sortie par défaut
    const char *input = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output = argv[++i];
            } else {
                printf("Option -o requiert un argument.\n");
                return 1;
            }
        } else {
            input = argv[i];
        }
    }

    if (input == NULL) {
        printf("Aucun fichier source spécifié.\n");
        return 1;
    }
    return Sasm(input, output);
}
