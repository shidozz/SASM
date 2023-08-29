#include "../include/sasm.h"
#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int Sasm(const char *inputF, const char *outputF) {
    char* input = readFile(inputF);
    
    char word[50];
    int wIndex = 0;

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

    for (int i = 0; i < instructionCount; i++) {
        if (instructions[i].errOpcode == KW_ERROR){
            if(strcmp(instructions[i].operand1.value, "ERROR") == 0)
                printf("Error: Bad token type used! This type of token (%s) can't be used in a %s opcode\n", TokenToString(instructions[i].operand1), KeywordToString(instructions[i].opcode));
            if(strcmp(instructions[i].operand2.value, "ERROR") == 0)
                printf("Error: Bad token type used! This type of token (%s) can't be used in a %s opcode\n", TokenToString(instructions[i].operand2), KeywordToString(instructions[i].opcode));
            return 1;
        } else if(instructions[i].opcode == KW_RET){
            printf("Instruction %d: Opcode=%s\n", i, KeywordToString(instructions[i].opcode));
        } else if(instructions[i].opcode == KW_GLOBAL || instructions[i].opcode == KW_EXTERN){
            printf("Instruction %d: Opcode=%s, Operand1= {type: %s, value: %s}\n", i, KeywordToString(instructions[i].opcode), TokenToString(instructions[i].operand1), instructions[i].operand1.value);
        } else{
            printf("Instruction %d: Opcode=%s, Operand1= {type: %s, value: %s}, Operand2={type: %s, value: %s}\n", i, KeywordToString(instructions[i].opcode), TokenToString(instructions[i].operand1), instructions[i].operand1.value, TokenToString(instructions[i].operand2), instructions[i].operand2.value);
        }
    }
    free(input);
    return 0;
}

