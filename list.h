#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

struct symbolList 
{
	struct symbolList* next;
	char* symbol;
	int val;
};

void setupSymbolTable(struct symbolList** head, struct symbolList** tail);
struct symbolList* createSymbol(struct symbolList* prev, char* symbol, int val);
void cleanupSymbolTable(struct symbolList** head);

#endif