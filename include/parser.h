#ifndef __PARSER_H__
#define __PARSER_H__

#include "lexer.h"
#include "utils.h"
#include <stdbool.h>
void parseTokens(struct Token tokens[], int tokenCount, struct Instruction instructions[], int *instructionCount);
bool isStatementGlobal(Token_t keyword, Token_t val);
bool isStatementExtern(Token_t keyword, Token_t val);
bool isStatementRet(Token_t keyword);
bool isStatementJII(Token_t keyword, Token_t val);
bool isStatementJIS(Token_t keyword, Token_t val);
bool isStatementJIN(Token_t keyword, Token_t val);
bool isStatementJIE(Token_t keyword, Token_t val);
bool isStatementVer(Token_t keyword, Token_t val1, Token_t val2);
bool isStatementSet(Token_t keyword, Token_t val1, Token_t val2);
bool isStatementRem(Token_t keyword, Token_t val1, Token_t val2);
bool isStatementAdd(Token_t keyword, Token_t val1, Token_t val2);
#endif