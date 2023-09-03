#ifndef __COMPILER_H__
#define __COMPILER_H__
#include <stdio.h>
#include <stdint.h>
#include "utils.h"


void Compile(Instruction_t* instruction, compiler_t *out);
#endif