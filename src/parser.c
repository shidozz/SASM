#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void parseTokens(struct Token tokens[], int tokenCount, struct Instruction instructions[], int *instructionCount) {
    int iCount = 0;
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == TOKEN_KEYWORD) {
            if ((i + 2 < tokenCount) && (isStatementAdd(tokens[i], tokens[i + 1], tokens[i + 2]))) {
                instructions[iCount].opcode = KW_ADD;
                instructions[iCount].operand1 = tokens[i + 1];
                instructions[iCount].operand2 = tokens[i + 2];
                iCount++;
                continue;
            } else if ((i + 2 < tokenCount) && isStatementRem(tokens[i], tokens[i + 1], tokens[i + 2])) {
                instructions[iCount].opcode = KW_REM;
                instructions[iCount].operand1 = tokens[i + 1];
                instructions[iCount].operand2 = tokens[i + 2];
                iCount++;
                continue;
            } else if ((i + 2 < tokenCount) && isStatementVer(tokens[i], tokens[i + 1], tokens[i + 2])) {
                instructions[iCount].opcode = KW_VER;
                instructions[iCount].operand1 = tokens[i + 1];
                instructions[iCount].operand2 = tokens[i + 2];
                iCount++;
                continue;
            } else if ((i + 2 < tokenCount) && isStatementSet(tokens[i], tokens[i + 1], tokens[i + 2])) {
                instructions[iCount].opcode = KW_SET;
                instructions[iCount].operand1 = tokens[i + 1];
                instructions[iCount].operand2 = tokens[i + 2];
                iCount++;
                continue;
            } else if ((i + 1 < tokenCount) && isStatementJII(tokens[i], tokens[i + 1])) {
                instructions[iCount].opcode = KW_JII;
                instructions[iCount].operand1 = tokens[i + 1];
                iCount++;
                continue;
            } else if ((i + 1 < tokenCount) && isStatementJIS(tokens[i], tokens[i + 1])) {
                instructions[iCount].opcode = KW_JIS;
                instructions[iCount].operand1 = tokens[i + 1];
                iCount++;
                continue;
            } else if ((i + 1 < tokenCount) && isStatementJIE(tokens[i], tokens[i + 1])) {
                instructions[iCount].opcode = KW_JIE;
                instructions[iCount].operand1 = tokens[i + 1];
                iCount++;
                continue;
            } else if ((i + 1 < tokenCount) && isStatementJIN(tokens[i], tokens[i + 1])) {
                instructions[iCount].opcode = KW_JIN;
                instructions[iCount].operand1 = tokens[i + 1];
                iCount++;
                continue;
            } else if ((i + 1 < tokenCount) && isStatementExtern(tokens[i], tokens[i + 1])) {
                instructions[iCount].opcode = KW_EXTERN;
                instructions[iCount].operand1 = tokens[i + 1];
                iCount++;
                continue;
            } else if ((i + 1 < tokenCount) && isStatementGlobal(tokens[i], tokens[i + 1])) {
                instructions[iCount].opcode = KW_GLOBAL;
                instructions[iCount].operand1 = tokens[i + 1];
                iCount++;
                continue;
            } else {
                if (isStatementRet(tokens[i])) {
                    instructions[iCount].opcode = KW_RET;
                } else {
                    instructions[iCount].errOpcode = KW_ERROR;
                    if(strcmp(tokens[i].value, "ret") == 0) 
                        instructions[iCount].opcode = KW_RET;
                }
            }

            if(instructions[iCount].errOpcode == KW_ERROR){
                iCount++;
                *instructionCount = iCount;
                return;
            }

            if (tokens[i + 1].type == TOKEN_OTHER) {
                instructions[iCount].errOpcode = KW_ERROR;
                instructions[iCount].operand1 = (Token_t){.type = instructions[iCount].operand1.type, .value = "ERROR"};
                iCount++;
                *instructionCount = iCount;
                return;
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

bool isStatementAdd(Token_t keyword, Token_t val1, Token_t val2) {
    if(strcmp(keyword.value, "add") == 0)
        if(val1.type == TOKEN_REGISTER || val1.type == TOKEN_NUMBER || val1.type == TOKEN_HEX)
            if(val2.type == TOKEN_REGISTER || val2.type == TOKEN_NUMBER || val2.type == TOKEN_HEX)
                return true;
    return false;
}

bool isStatementRem(Token_t keyword, Token_t val1, Token_t val2) {
    if(strcmp(keyword.value, "rem") == 0)
        if(val1.type == TOKEN_REGISTER || val1.type == TOKEN_NUMBER || val1.type == TOKEN_HEX)
            if(val2.type == TOKEN_REGISTER || val2.type == TOKEN_NUMBER || val2.type == TOKEN_HEX)
                return true;
    return false;
}

bool isStatementSet(Token_t keyword, Token_t val1, Token_t val2) {
    if(strcmp(keyword.value, "set") == 0)
        if(val1.type == TOKEN_REGISTER)
            if(val2.type == TOKEN_REGISTER || val2.type == TOKEN_NUMBER || val2.type == TOKEN_HEX)
                return true;
    return false;
}

bool isStatementVer(Token_t keyword, Token_t val1, Token_t val2) {
    if(strcmp(keyword.value, "ver") == 0)
        if(val1.type == TOKEN_REGISTER || val1.type == TOKEN_NUMBER || val1.type == TOKEN_HEX)
            if(val2.type == TOKEN_REGISTER || val2.type == TOKEN_NUMBER || val2.type == TOKEN_HEX)
                return true;
    return false;
}
bool isStatementJII(Token_t keyword, Token_t val) {
    if(strcmp(keyword.value, "jii") == 0)
        if(val.type == TOKEN_LABEL)
            return true;
    return false;
}
bool isStatementJIS(Token_t keyword, Token_t val) {
    if(strcmp(keyword.value, "jis") == 0)
        if(val.type == TOKEN_LABEL)
            return true;
    return false;
}
bool isStatementJIN(Token_t keyword, Token_t val) {
    if(strcmp(keyword.value, "jin") == 0)
        if(val.type == TOKEN_LABEL)
            return true;
    return false;
}

bool isStatementJIE(Token_t keyword, Token_t val) {
    if(strcmp(keyword.value, "jie") == 0)
        if(val.type == TOKEN_LABEL)
            return true;
    return false;
}

bool isStatementExtern(Token_t keyword, Token_t val) {
    if(strcmp(keyword.value, "extern") == 0)
        if(val.type == TOKEN_LABEL)
            return true;
    return false;
}

bool isStatementGlobal(Token_t keyword, Token_t val) {
    if(strcmp(keyword.value, "global") == 0)
        if(val.type == TOKEN_LABEL)
            return true;
    return false;
}

bool isStatementRet(Token_t keyword) {
    return (strcmp(keyword.value, "ret") == 0) ? true : false;
}
