#include "parser.h"

//Cleans a line by removing whitespace.
char* getCleanLine(char* in)
{
	int size = strlen(in);
	char* out = malloc( sizeof(char) * ( size + 1 ) );
	int i = 0;
	int outsize = 0;
	for(i = 0; i < size; i++)
	{
		if(in[i] == '/')
			break;
		if(isspace(in[i]))
		{
			if(in[i] == '\n')
				break;
			continue;
		}
		out[outsize++] = in[i];
		
	}
	out[outsize] = '\0';
	return out;
}

//Takes a clean line and returns the destination token
void getDest(char* in, char* out)
{
	char* destExists = strchr(in, '=');
	if(destExists == NULL)
	{
		out[0] = '\0';
		return;
	}
	int i = 0;
	int end = destExists - in;
	for (i = 0; i < end; i++)
	{
		out[i] = in[i];
	}
	out[i] = '\0';
}

//Takes a clean line and returns the computation token
void getComp(char* in, char* out)
{
	char* destExists = strchr(in, '=');
	int i = 0,j = 0;
	if (destExists != NULL)
		i = destExists - in + 1;
	while(1)
	{
		out[j++] = in[i++];
		if(in[i] == '\0' || in[i] == ';')
			break;
		
	}
	out[j]='\0';
	return;
}

//Takes a clean line and returns a jump token.
void getJump(char* in, char* out)
{
	char* jumpExists = strchr(in, ';');
	if(jumpExists == NULL)
	{
		out[0] = '\0';
		return;
	}
	int i;
	for (i =1; i<4; i++)
		out[i-1] = jumpExists[i];
	out[3] = '\0'; 
}

//Takes a clean line and returns the memory address.
void getSymbolValue(char* in, char* out)
{
	strncpy(out,in+1, 5);
	out[5] = '\0';
}

//Takes a clean line and returns a ParsedCommand struct
struct ParsedCommand* getParsedCommand(char* in)
{
	struct ParsedCommand* p = malloc(sizeof(struct ParsedCommand));
	p->ct = getCommandType(in);
	
	if(p->ct == A_TYPE)
	{
		p->symbol = NULL;
		getSymbolValue(in, p->memLocation);
	}
	if(p->ct == C_TYPE)
	{
		getDest(in, p->dest);
		getComp(in, p->comp);
		getJump(in, p->jump);
	}
	return p;	
}

//Takes a clean line and returns the CommandType
enum CommandType getCommandType(char* in)
{
	if (in[0] == '@')
		return A_TYPE;
	if (in[0] == '(')
		return L_TYPE;
	return C_TYPE;
}

void freeParsedCommand(struct ParsedCommand* p)
{
	free(p);
}
