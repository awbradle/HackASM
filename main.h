#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code.h"
#include "list.h"

void handleFileIO(FILE** in, FILE** out, char* inName);
void cleanInput(FILE* in, FILE* out);
void writeOut(FILE* out);

struct list 
{
	struct list* next;
	char* line;
};

#endif