#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

char* getCleanLine(char* in);
void getDest(char* in, char* out);
void getComp(char* in, char* out);
void getJump(char* in, char* out);
void getSymbolValue(char* in, char* out);
enum CommandType getCommandType(char* in);
struct ParsedCommand* getParsedCommand(char* in);
void freeParsedCommand(struct ParsedCommand* p);
void findOrCreateSymbol(char* in, char* out);
void processLabel(char* cleanLine, int lineCount);
void setupParserSymbolTable();
void cleanupParserSymbolTable();

enum CommandType {
	C_TYPE,
	A_TYPE,
	L_TYPE
};

struct ParsedCommand {
	enum CommandType ct;
	char memLocation[6];
	char dest[4];
	char comp[4];
	char jump[4];
};

#endif