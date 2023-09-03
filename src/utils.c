#include "../include/utils.h"
#include "../include/compiler.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

registres_t registre_Compiler = (registres_t){
   A: {"A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9"},
   B: {"B0", "B1", "B2", "B3", "B4"},
};

int isInteger(char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    if (*endptr == '\0') {
        return 1;
    }
    return 0;
}

int appendBytecodesToFile(const char *filename, compiler_t *bytecodes, size_t len) {
    FILE *fp = fopen(filename, "ab");
    if (fp == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", filename);
        return -1;
    }

    size_t written = fwrite(bytecodes->bytecode, sizeof(uint32_t), len, fp);
    fclose(fp);

    if (written != len) {
        fprintf(stderr, "Écriture incomplète dans le fichier %s.\n", filename);
        return -1;
    }

    return 0;
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        fclose(file);
        return 1;
    }

    return 0;
}

int writeFile(const char *filename, uint32_t data[], size_t dataSize) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s pour l'écriture.\n", filename);
        return -1;
    }

    size_t writtenSize = fwrite(data, 1, dataSize, file);
    if (writtenSize != dataSize) {
        printf("Erreur lors de l'écriture dans le fichier. Écrit : %zu, Attendu : %zu.\n", writtenSize, dataSize);
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}
char *readFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);

    long filesize = ftell(file);

    fseek(file, 0, SEEK_SET);

    
    char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        printf("Échec de l'allocation de mémoire.\n");
        fclose(file);
        return NULL;
    }

    
    fread(buffer, 1, filesize, file);

    
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

int readByteFile(const char *filename, uint32_t **bytecodes32, size_t *n32) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier %s pour le lecture.\n", filename);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    size_t total_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    *n32 = total_size / sizeof(uint32_t);

    *bytecodes32 = malloc(*n32 * sizeof(uint32_t));

    if (*bytecodes32 == NULL) {
        printf("Échec de l'allocation de mémoire.\n");
        fclose(fp);
        return -1;
    }

    fread(*bytecodes32, sizeof(uint32_t), *n32, fp);

    fclose(fp);

    return 0;
}


void showFile(const char *filename) {
    uint32_t *bytecodes32;
    size_t n32;

    if (readByteFile(filename, &bytecodes32, &n32) == -1) {
        printf("Erreur lors de la lecture du fichier.\n");
        return;
    }

    printf("Valeurs uint32_t:\n");
    for (size_t i = 0; i < n32; ++i) {
        printf("%u ", bytecodes32[i]);
    }
    printf("\n");

    free(bytecodes32);
}

uint32_t used_addresses[1000];
char *used_label[1000];
int used_count = 0;

int is_address_used(uint32_t address) {
    for (int i = 0; i < used_count; i++) {
        if (used_addresses[i] == address) {
            return 1;
        }
    }
    return 0;
}
int is_label_used(char *label) {
    for (int i = 0; i < used_count; i++) {
        if (strcmp(used_label[i], label) == 0) {
            return 1;
        }
    }
    return 0;
}

uint32_t address_of(char *label) {
    for (int i = 0; i < used_count; i++) {
        if (strcmp(used_label[i], label) == 0) {
            return used_addresses[i];
        }
    }
    return 0;
}
char *label_of(uint32_t address) {
    for (int i = 0; i < used_count; i++) {
        if (used_addresses[i] == address) {
            return used_label[i];
        }
    }
    return 0;
}

void createLabel(char *name, label_t *label) {
    if(is_label_used(name) == 1) {
        fprintf(stderr, "Impossible de creer le label %s car il existe deja.\n", name);
        exit(1);
    }else{
        label->name = strdup(name);  
        used_label[used_count] = label->name;
        used_count++;
    }
    uint32_t random_address;
    do {
        random_address = rand() % 0xFFFFFFFF;  
    } while (is_address_used(random_address));  

    label->address = random_address;
    used_addresses[used_count++] = random_address;  
}