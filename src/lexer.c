#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum TokenType identifyToken(char *str) {
    const char *keywords[] = {"ret", "add", "rem", "set", "jmp", "ver", "jie", "jin", "jis", "jii", "global", "extern", NULL};
    const char *registers[] = {"A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "B0", "B1", "B2", "B3", "B4", "ST", "PR", "CR", "NX", NULL};

    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) return TOKEN_KEYWORD;
    }
    for (int i = 0; registers[i] != NULL; i++) {
        if (strcmp(str, registers[i]) == 0) return TOKEN_REGISTER;
    }
    if (strlen(str) > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        return TOKEN_HEX;
    }
    if (isInteger(str) == 1) return TOKEN_NUMBER;
    if (str[0] == '_') {
        return TOKEN_LABEL;
    }
    return TOKEN_OTHER;
}