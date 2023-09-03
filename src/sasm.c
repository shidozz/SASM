#include "../include/sasm.h"
#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/compiler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int Sasm(const char *inputF, const char *outputF) {
    char* input = readFile(inputF);
    
    char word[50];
    int wIndex = 0;
    compiler_t *out = (compiler_t *)malloc(sizeof(compiler_t));
    struct Token tokens[100];
    int tIndex = 0;

    for (int i = 0; i <= strlen(input); i++) {
        char c = input[i];
        if (isspace(c) || c == '\0') {
            if (wIndex > 0) {
                word[wIndex] = '\0';
                tokens[tIndex].type = identifyToken(word);
                strcpy(tokens[tIndex].value, word);
                tIndex++;
                wIndex = 0;
            }
        } else {
            word[wIndex++] = c;
        }
    }

    struct Instruction instructions[50];
    int instructionCount = 0;
    parseTokens(tokens, tIndex, instructions, &instructionCount);
    if(file_exists(outputF))
    {
        remove(outputF);
    }
    for (int i = 0; i < instructionCount; i++) {
        if (instructions[i].errOpcode == KW_ERROR){
            if(strcmp(instructions[i].operand1.value, "ERROR") == 0)
                fprintf(stderr, "Error(%s : %d): Bad token type used! This type of token (%s) can't be used in a %s opcode\n", inputF, i, TokenToString(instructions[i].operand1), KeywordToString(instructions[i].opcode));
            if(strcmp(instructions[i].operand2.value, "ERROR") == 0)
                fprintf(stderr, "Error(%s : %d): Bad token type used! This type of token (%s) can't be used in a %s opcode\n", inputF, i, TokenToString(instructions[i].operand2), KeywordToString(instructions[i].opcode));
            
            exit(1);
        }
        Compile(&instructions[i], out);
        appendBytecodesToFile(outputF, out, sizeof(out));
    }

    printf("\n");
    showFile(outputF);
    free(input);
    return 0;
}

