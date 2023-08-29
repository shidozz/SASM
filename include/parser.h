#ifndef __PARSER_H__
#define __PARSER_H__

#include "lexer.h"
#include "utils.h"

void parseTokens(struct Token tokens[], int tokenCount, struct Instruction instructions[], int *instructionCount);

#endif