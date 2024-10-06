#include "list.h" 

//Setup symbol table
void setupSymbolTable(struct symbolList** head, struct symbolList** tail)
{
	struct symbolList* curr = NULL;
	curr = createSymbol(curr, "SP", 0);
	*head = curr;
	
	curr = createSymbol(curr, "LCL", 1);
	curr = createSymbol(curr, "ARG", 2);
	curr = createSymbol(curr, "THIS", 3);
	curr = createSymbol(curr, "THAT", 4);
	
	curr = createSymbol(curr, "R0", 0);
	curr = createSymbol(curr, "R1", 1);
	curr = createSymbol(curr, "R2", 2);
	curr = createSymbol(curr, "R3", 3);
	curr = createSymbol(curr, "R4", 4);
	curr = createSymbol(curr, "R5", 5);
	curr = createSymbol(curr, "R6", 6);
	curr = createSymbol(curr, "R7", 7);
	curr = createSymbol(curr, "R8", 8);
	curr = createSymbol(curr, "R9", 9);
	curr = createSymbol(curr, "R10", 10);
	curr = createSymbol(curr, "R11", 11);
	curr = createSymbol(curr, "R12", 12);
	curr = createSymbol(curr, "R13", 13);
	curr = createSymbol(curr, "R14", 14);
	curr = createSymbol(curr, "R15", 15);
	
	curr = createSymbol(curr, "SCREEN", 16384);
	curr = createSymbol(curr, "KBD", 24576);
	*tail = curr;
}

//Create a symbol helper function
struct symbolList* createSymbol(struct symbolList* prev, char* symbol, int val)
{
	struct symbolList* curr;
	curr = malloc(sizeof(struct symbolList));
	if(prev)
		prev->next = curr;
	int len = strlen(symbol);
	curr->symbol = malloc(len + 1);
	strncpy(curr->symbol, symbol, len+1);
	curr ->val = val;
	return curr;
}

//Clean up the symbol table
void cleanupSymbolTable(struct symbolList** head)
{
	struct symbolList* curr;
	struct symbolList* prev;
	curr = *head;
	
	while(curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		free(prev->symbol);
		free(prev);
	}
}