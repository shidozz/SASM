#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdint.h>
typedef struct compiler{
    uint32_t bytecode[4];
} compiler_t;
typedef struct label {
    char *name;
    uint32_t address;
} label_t;
char *readFile(const char *filename);
int writeFile(const char *filename, uint32_t data[], size_t dataSize);
int readByteFile(const char *filename, uint32_t **bytecodes32, size_t *n32);
int appendBytecodesToFile(const char *filename, compiler_t *bytecodes, size_t len);
void showFile(const char *filename);
int file_exists(const char *filename);
int isInteger(char *str);
void createLabel(char *name, label_t *label);
int is_address_used(uint32_t address);
int is_label_used(char *name);
uint32_t address_of(char *label);
char *label_of(uint32_t address);
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


typedef struct registres {
    char *A[10];
    char *B[5];
} registres_t;


extern registres_t registre_Compiler;
char *TokenToString(Token_t token);
char *KeywordToString(enum KeywordType keyword);
#endif