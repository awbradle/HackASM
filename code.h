#ifndef CODE_H
#define CODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void getBinDest(char* in, char* out);
void getBinJump(char* in, char* out);
void getBinComp(char* in, char* out);
void getBinAddress(char* in, char* out);
void getABinary(char* addr, char* out); 
void getCBinary(char* dest, char* comp, char* jump, char* out);
void getBinOut(struct ParsedCommand* p, char* out);

#endif