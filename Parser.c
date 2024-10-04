#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum CommandType {
	C_TYPE,
	A_TYPE,
	L_TYPE
};

struct ParsedCommand {
	enum CommandType ct;
	char* symbol;
	char symbolValue[6];
	char dest[4];
	char comp[4];
	char jump[4];
};

char* cleanLine(char* in);
void getDest(char* in, char* out);
void getComp(char* in, char* out);
void getJump(char* in, char* out);
enum CommandType getCommandType(char* in);
struct ParsedCommand* getParsedCommand(char* in);

int main(int argc, char* argv[])
{
	printf("%ld\n", strlen("\n"));
}	
		
char* cleanLine(char* in)
{
	int size = strlen(in);
	char *out = malloc( sizeof(char) * ( size + 1 ) );
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
	if(in[size - 1] == '\n' && outsize > 0)
		out[outsize++] = '\n';
	out[outsize] = '\0';
	return out;
}

void getDest(char* in, char* out)
{
	char *destExists = strchr(in, '=');
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

void getComp(char* in, char* out)
{
	char *destExists = strchr(in, '=');
	int i = 0,j = 0;
	if (destExists != NULL)
		i = destExists - in + 1;
	while(1)
	{
		out[j++] = in[i++];
		if(in[i] == '\0' || in[i] == '\n' || in[i] == ';')
			break;
		
	}
	out[j]='\0';
	return;
}

void getJump(char* in, char* out)
{
	char *jumpExists = strchr(in, ';');
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

struct ParsedCommand* getParsedCommand(char* in)
{
	struct ParsedCommand* p = malloc(sizeof(struct ParsedCommand));
	p->ct = getCommandType(in);
	if(p->ct == C_TYPE)
	{
		getDest(in, p->dest);
		getComp(in, p->comp);
		getJump(in, p->jump);
	}
	else if(p->ct == A_TYPE)
	{
	 return p;
	}
	return p;	
}

enum CommandType getCommandType(char* in)
{
	if (in[0] == '@')
		return A_TYPE;
	if (in[0] == '(')
		return L_TYPE;
	return C_TYPE;
}