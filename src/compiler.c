#include "../include/compiler.h"
#include "../include/utils.h"
#include "../include/sasm.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void Compile(Instruction_t* instruction, compiler_t *array){
    char *endptr;
    if(instruction->errOpcode == KW_ERROR) {
        if(strcmp(instruction->operand1.value, "ERROR") == 0)
            fprintf(stderr, "Error: Bad token type used! This type of token (%s) can't be used in a %s opcode\n", TokenToString(instruction->operand1), KeywordToString(instruction->opcode));
        if(strcmp(instruction->operand2.value, "ERROR") == 0)
            fprintf(stderr, "Error: Bad token type used! This type of token (%s) can't be used in a %s opcode\n", TokenToString(instruction->operand2), KeywordToString(instruction->opcode));
        exit(1);
    }
    switch (instruction->opcode)
    {
        case KW_ADD:
            array->bytecode[0] = KW_ADD;
            array->bytecode[3] = (instruction->operand1.type == TOKEN_REGISTER && instruction->operand2.type == TOKEN_REGISTER) ? 3 : (instruction->operand1.type == TOKEN_REGISTER) ? 1 : (instruction->operand2.type == TOKEN_REGISTER) ? 2 : 0;
            if(instruction->operand1.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand1.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[1] = (uint16_t) i;
                    } else if (i < 5){
                        if (strcmp(instruction->operand1.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[1] = (uint32_t ) 10 + i;
                    }
                }
            }
            if(instruction->operand2.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand2.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[2] = (uint16_t) i;
                    } else if (i < 5){
                        if (strcmp(instruction->operand2.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[2] = (uint32_t ) 10 + i;
                    }
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 8){ // Hexadecimal de 32 bits
                array->bytecode[2] = (uint32_t ) strtoul(instruction->operand2.value, &endptr,0);
            } else if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 4){ // Hexadecimal de 16 bits
                array->bytecode[2] = (uint16_t) strtoul(instruction->operand2.value, &endptr,0);
            }

            if(instruction->operand1.type == TOKEN_NUMBER){
                array->bytecode[1] = (uint32_t) strtoul(instruction->operand1.value, &endptr,0);
            }
            if(instruction->operand2.type == TOKEN_NUMBER){
                array->bytecode[2] = (uint32_t) strtoul(instruction->operand2.value, &endptr,0);
            }
            printf("opcode: %s token 1: %s token 2: %s\n", KeywordToString(instruction->opcode), TokenToString(instruction->operand1), TokenToString(instruction->operand2));
            printf("[Bytecode] opcode: %u token 1: %u token 2: %u type: %u\n", array->bytecode[0], array->bytecode[1], array->bytecode[2], array->bytecode[3]);
            break;
        case KW_REM:
            array->bytecode[0] = KW_REM;
            array->bytecode[3] = (instruction->operand1.type == TOKEN_REGISTER && instruction->operand2.type == TOKEN_REGISTER) ? 3 : (instruction->operand1.type == TOKEN_REGISTER) ? 1 : (instruction->operand2.type == TOKEN_REGISTER) ? 2 : 0;
            if(instruction->operand1.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand1.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[1] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand1.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[1] = (uint32_t ) 10 + i;
                    }
                }
            }
            if(instruction->operand2.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand2.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[2] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand2.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[2] = (uint32_t ) 10 + i;
                    }
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 8){ // Hexadecimal de 32 bits
                array->bytecode[2] = (uint32_t ) strtoul(instruction->operand2.value, &endptr,0);
            } else if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 4){ // Hexadecimal de 16 bits
                array->bytecode[2] = (uint16_t) strtoul(instruction->operand2.value, &endptr,0);
            }
            if(instruction->operand1.type == TOKEN_NUMBER){
                array->bytecode[1] = (uint32_t) strtoul(instruction->operand1.value, &endptr,0);
            }
            if(instruction->operand2.type == TOKEN_NUMBER){
                array->bytecode[2] = (uint32_t) strtoul(instruction->operand2.value, &endptr,0);
            }
            
            printf("opcode: %s token 1: %s token 2: %s\n", KeywordToString(instruction->opcode), TokenToString(instruction->operand1), TokenToString(instruction->operand2));
            printf("[Bytecode] opcode: %u token 1: %u token 2: %u type: %u\n", array->bytecode[0], array->bytecode[1], array->bytecode[2], array->bytecode[3]);
            break;
        
        case KW_VER:
            array->bytecode[0] = KW_VER;
            array->bytecode[3] = (instruction->operand1.type == TOKEN_REGISTER && instruction->operand2.type == TOKEN_REGISTER) ? 3 : (instruction->operand1.type == TOKEN_REGISTER) ? 1 : (instruction->operand2.type == TOKEN_REGISTER) ? 2 : 0;
            if(instruction->operand1.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand1.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[1] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand1.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[1] = (uint32_t ) 10 + i;
                    }
                }
            }
            if(instruction->operand2.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand2.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[2] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand2.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[2] = (uint32_t ) 10 + i;
                    }
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 8){ // Hexadecimal de 32 bits
                array->bytecode[2] = (uint32_t ) strtoul(instruction->operand2.value, &endptr,0);
            } else if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 4){ // Hexadecimal de 16 bits
                array->bytecode[2] = (uint16_t) strtoul(instruction->operand2.value, &endptr,0);
            }
            if(instruction->operand1.type == TOKEN_NUMBER){
                array->bytecode[1] = (uint32_t) strtoul(instruction->operand1.value, &endptr,0);
            }
            if(instruction->operand2.type == TOKEN_NUMBER){
                array->bytecode[2] = (uint32_t) strtoul(instruction->operand2.value, &endptr,0);
            }
            printf("opcode: %s token 1: %s token 2: %s\n", KeywordToString(instruction->opcode), TokenToString(instruction->operand1), TokenToString(instruction->operand2));
            printf("[Bytecode] opcode: %u token 1: %u token 2: %u type: %u\n", array->bytecode[0], array->bytecode[1], array->bytecode[2], array->bytecode[3]);
            break;
        case KW_SET:
            array->bytecode[0] = KW_SET;
            array->bytecode[3] = (instruction->operand1.type == TOKEN_REGISTER && instruction->operand2.type == TOKEN_REGISTER) ? 3 : (instruction->operand1.type == TOKEN_REGISTER) ? 1 : (instruction->operand2.type == TOKEN_REGISTER) ? 2 : 0;
            if(instruction->operand1.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand1.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[1] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand1.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[1] = (uint32_t ) 10 + i;
                    }
                }
            }
            if(instruction->operand2.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if (strcmp(instruction->operand2.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[2] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand2.value, registre_Compiler.B[i]) == 0)
                            array->bytecode[2] = (uint32_t ) 10 + i;
                    }
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 8){ // Hexadecimal de 32 bits
                array->bytecode[2] = (uint32_t ) strtoul(instruction->operand2.value, &endptr, 0);
            } else if(instruction->operand2.type == TOKEN_HEX && strlen(instruction->operand2.value) == 4){ // Hexadecimal de 16 bits
                array->bytecode[2] = (uint16_t) strtoul(instruction->operand2.value, &endptr, 0);
            }

            if(instruction->operand2.type == TOKEN_NUMBER){
                array->bytecode[2] = (uint32_t) strtoul(instruction->operand2.value, &endptr, 0);
            }
            
            printf("opcode: %s token 1: %s token 2: %s\n", KeywordToString(instruction->opcode), TokenToString(instruction->operand1), TokenToString(instruction->operand2));
            printf("[Bytecode] opcode: %u token 1: %u token 2: %u type: %u\n", array->bytecode[0], array->bytecode[1], array->bytecode[2], array->bytecode[3]);
            break;

        case KW_RET:
            array->bytecode[0] = (uint32_t )KW_RET;
            array->bytecode[1] = (uint32_t )0;
            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;
        case KW_GLOBAL:
            array->bytecode[0] = (uint32_t )KW_GLOBAL;
            if(instruction->operand1.type == TOKEN_LABEL){
                label_t label;
                createLabel(instruction->operand1.value, &label);
                printf("Label name: %s\n", label.name);
                printf("Label address: %u\n", label.address);
                array->bytecode[1] = label.address;
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }
            
            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;
        case KW_JIE:
            array->bytecode[0] = (uint32_t )KW_JIE;
            if(instruction->operand1.type == TOKEN_LABEL){
                if(is_label_used(instruction->operand1.value) == 1){
                    array->bytecode[1] = address_of(instruction->operand1.value);
                }else{
                    fprintf(stderr, "Label %s not found\n", instruction->operand1.value);
                    exit(1);
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;

        case KW_JII:
            array->bytecode[0] = (uint32_t )KW_JII;
            if(instruction->operand1.type == TOKEN_LABEL){
                if(is_label_used(instruction->operand1.value) == 1){
                    array->bytecode[1] = address_of(instruction->operand1.value);
                }else{
                    fprintf(stderr, "Label %s not found\n", instruction->operand1.value);
                    exit(1);
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;
        
        case KW_JIN:
            array->bytecode[0] = (uint32_t )KW_JIN;
            if(instruction->operand1.type == TOKEN_LABEL){
                if(is_label_used(instruction->operand1.value) == 1){
                    array->bytecode[1] = address_of(instruction->operand1.value);
                }else{
                    fprintf(stderr, "Label %s not found\n", instruction->operand1.value);
                    exit(1);
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;
        case KW_JIS:
            array->bytecode[0] = (uint32_t )KW_JIS;
            if(instruction->operand1.type == TOKEN_LABEL){
                if(is_label_used(instruction->operand1.value) == 1){
                    array->bytecode[1] = address_of(instruction->operand1.value);
                }else{
                    fprintf(stderr, "Label %s not found\n", instruction->operand1.value);
                    exit(1);
                }
            }

            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }

            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;

        case KW_EXTERN:
            array->bytecode[0] = (uint32_t)KW_EXTERN;
            if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 8) { // Hexadecimal de 32 bits
                array->bytecode[1] = (uint32_t ) strtoul(instruction->operand1.value, &endptr,0);
                
            } else if(instruction->operand1.type == TOKEN_HEX && strlen(instruction->operand1.value) == 4) { // Hexadecimal de 16 bits
                array->bytecode[1] = (uint16_t) strtoul(instruction->operand1.value, &endptr,0);
            }
            if(instruction->operand1.type == TOKEN_REGISTER){
                for(int i = 0; i < (10); i++){
                    if(strcmp(instruction->operand1.value, registre_Compiler.A[i]) == 0){
                        array->bytecode[1] = (uint16_t) i;
                    } else if (i < 5){
                        if(strcmp(instruction->operand1.value, registre_Compiler.B[i]) == 0)
                        array->bytecode[1] = (uint32_t ) 10 + i;
                    }
                }
            }
            array->bytecode[2] = (uint32_t )0;
            array->bytecode[3] = (uint32_t )0;
            break;
        default:
            break;
    }
}