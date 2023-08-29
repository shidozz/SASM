#include "../include/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int isInteger(char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    if (*endptr == '\0') {
        return 1;
    }
    return 0;
}

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", filename);
        return NULL;
    }

    // Se positionner à la fin du fichier
    fseek(file, 0, SEEK_END);

    // Obtenir la taille du fichier
    long filesize = ftell(file);

    // Se repositionner au début du fichier
    fseek(file, 0, SEEK_SET);

    // Allouer de la mémoire pour contenir le fichier + le caractère de fin de chaîne
    char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        printf("Échec de l'allocation de mémoire.\n");
        fclose(file);
        return NULL;
    }

    // Lire le fichier dans le buffer
    fread(buffer, 1, filesize, file);

    // Ajouter le caractère de fin de chaîne
    buffer[filesize] = '\0';

    fclose(file);
    return buffer;
}

char *KeywordToString(enum KeywordType keyword){
    switch(keyword){
        case KW_GLOBAL:
            return "KW_GLOBAL";
        case KW_EXTERN:
            return "KW_EXTERN";
        case KW_RET:
            return "KW_RET";
        case KW_ADD:
            return "KW_ADD";
        case KW_REM:
            return "KW_REM";
        case KW_JII:
            return "KW_JII";
        case KW_JIE:
            return "KW_JIE";
        case KW_JIS:
            return "KW_JIS";
        case KW_JIN:
            return "KW_JIN";
        case KW_SET:
            return "KW_SET";
        case KW_VER:
            return "KW_VER";
        case KW_ERROR:
            return "KW_ERROR";
        default:
            return "KW_ERROR";
    }
}

char *TokenToString(Token_t token){
    switch(token.type){
        case TOKEN_KEYWORD:
            return "TOKEN_KEYWORD";
        case TOKEN_REGISTER:
            return "TOKEN_REGISTER";
        case TOKEN_HEX:
            return "TOKEN_HEX";
        case TOKEN_NUMBER:
            return "TOKEN_NUMBER";
        case TOKEN_LABEL:
            return "TOKEN_LABEL";
        case TOKEN_OTHER:
            return "TOKEN_OTHER";
        default:
            return "TOKEN_OTHER";
    }
}