#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void parseTokens(struct Token tokens[], int tokenCount, struct Instruction instructions[], int *instructionCount) {
    int iCount = 0;
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == TOKEN_KEYWORD) {
            if (strcmp(tokens[i].value, "global") == 0) {
                instructions[iCount].opcode = KW_GLOBAL;
            } else if (strcmp(tokens[i].value, "extern") == 0) {
                instructions[iCount].opcode = KW_EXTERN;
            } else if (strcmp(tokens[i].value, "add") == 0) {
                instructions[iCount].opcode = KW_ADD;
            } else if (strcmp(tokens[i].value, "rem") == 0) {
                instructions[iCount].opcode = KW_REM;
            } else if (strcmp(tokens[i].value, "ret") == 0) {
                instructions[iCount].opcode = KW_RET;
                iCount++;
                continue;
            } else if (strcmp(tokens[i].value, "set") == 0) {
                instructions[iCount].opcode = KW_SET;
            } else if (strcmp(tokens[i].value, "JII") == 0) {
                instructions[iCount].opcode = KW_JII;
            } else if (strcmp(tokens[i].value, "JIS") == 0) {
                instructions[iCount].opcode = KW_JIS;
            } else if (strcmp(tokens[i].value, "JIE") == 0) {
                instructions[iCount].opcode = KW_JIE;
            } else if (strcmp(tokens[i].value, "JIN") == 0) {
                instructions[iCount].opcode = KW_JIN;
            } else if (strcmp(tokens[i].value, "VER") == 0) {
                instructions[iCount].opcode = KW_VER;
            }

            if (i + 1 < tokenCount && (tokens[i + 1].type == TOKEN_REGISTER || tokens[i + 1].type == TOKEN_HEX || tokens[i + 2].type == TOKEN_NUMBER || tokens[i + 1].type == TOKEN_LABEL)) {
                instructions[iCount].operand1 = tokens[i + 1];
            }
            if (tokens[i + 1].type == TOKEN_OTHER) {
                instructions[iCount].errOpcode = KW_ERROR;
                instructions[iCount].operand2 = (Token_t){.type = instructions[iCount].operand1.type, .value = "ERROR"};
                iCount++;
                *instructionCount = iCount;
                return;
            }
            if (i + 2 < tokenCount && (tokens[i + 2].type == TOKEN_REGISTER || tokens[i + 2].type == TOKEN_HEX || tokens[i + 2].type == TOKEN_NUMBER)) {
                instructions[iCount].operand2 = tokens[i + 2];
            }
            if (tokens[i + 2].type == TOKEN_OTHER) {
                instructions[iCount].errOpcode = KW_ERROR;
                instructions[iCount].operand2 = (Token_t){.type = instructions[iCount].operand2.type, .value = "ERROR"};
                iCount++;
                *instructionCount = iCount;
                return;
            }
            
            iCount++;
        }
    }
    *instructionCount = iCount;
}