#ifndef __UTILS_H__
#define __UTILS_H__
char *readFile(const char *filename);
int isInteger(char *str);
enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_REGISTER,
    TOKEN_HEX,
    TOKEN_NUMBER,
    TOKEN_LABEL,
    TOKEN_OTHER,
};

enum KeywordType {
    KW_GLOBAL,
    KW_EXTERN,
    KW_RET,
    KW_ADD,
    KW_REM,
    KW_JII,
    KW_JIE,
    KW_JIS,
    KW_JIN,
    KW_SET,
    KW_VER,
    KW_ERROR,
};

typedef struct Token {
    enum TokenType type;
    char value[50];
} Token_t;

typedef struct Instruction {
    enum KeywordType opcode;
    enum KeywordType errOpcode;
    Token_t operand1;
    Token_t operand2;
} Instruction_t;

char *TokenToString(Token_t token);
char *KeywordToString(enum KeywordType keyword);

#endif