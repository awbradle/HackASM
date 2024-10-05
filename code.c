#include "code.h"
#include "parser.h"

//takes a dest token and returns binary string
void getBinDest(char* in, char* out)
{
	strcpy(out, "000");
	if(in == NULL || strcmp(in, "") == 0)
		return;
	
	int i;
	for(i = 0; i < 3; i++)
	{
		if(in[i] == '\0')
			return;
		if(in[i] == 'A')
			out[0] = '1';
		if(in[i] == 'D')
			out[1] = '1';
		if(in[i] == 'M')
			out[2] = '1';
	}
}

//takes a jump token and returns binary string
void getBinJump(char* in, char* out)
{
	if(in == NULL || strcmp(in, "") == 0)
		strcpy(out, "000");
	else if(strcmp(in, "JGT") == 0)
		strcpy(out, "001");
	else if(strcmp(in, "JEQ") == 0)
		strcpy(out, "010");
	else if(strcmp(in, "JGE") == 0)
		strcpy(out, "011");
	else if(strcmp(in, "JLT") == 0)
		strcpy(out, "100");
	else if(strcmp(in, "JNE") == 0)
		strcpy(out, "101");
	else if(strcmp(in, "JLE") == 0)
		strcpy(out, "110");
	else if(strcmp(in, "JMP") == 0)
		strcpy(out, "111");
}

//takes a comp token and returns binary string
void getBinComp(char* in, char* out)
{
	if (strchr(in, 'M') == NULL)
	{
		if(strcmp(in, "0") == 0)
			strcpy(out, "0101010");
		else if(strcmp(in, "1") == 0)
			strcpy(out, "0111111");
		else if(strcmp(in, "-1") == 0)
			strcpy(out, "0111010");
		else if(strcmp(in, "D") == 0)
			strcpy(out, "0001100");
		else if(strcmp(in, "A") == 0)
			strcpy(out, "0110000");
		else if(strcmp(in, "!D") == 0)
			strcpy(out, "0001101");
		else if(strcmp(in, "!A") == 0)
			strcpy(out, "0110001");
		else if(strcmp(in, "-D") == 0)
			strcpy(out, "0001111");
		else if(strcmp(in, "-A") == 0)
			strcpy(out, "0110011");
		else if(strcmp(in, "D+1") == 0)
			strcpy(out, "0011111");
		else if(strcmp(in, "A+1") == 0)
			strcpy(out, "0110111");
		else if(strcmp(in, "D-1") == 0)
			strcpy(out, "0001110");
		else if(strcmp(in, "A-1") == 0)
			strcpy(out, "0110010");
		else if(strcmp(in, "D+A") == 0)
			strcpy(out, "0000010");
		else if(strcmp(in, "D-A") == 0)
			strcpy(out, "0010011");
		else if(strcmp(in, "A-D") == 0)
			strcpy(out, "0000111");
		else if(strcmp(in, "D&A") == 0)
			strcpy(out, "0000000");
		else if(strcmp(in, "D|A") == 0)
			strcpy(out, "0010101");
	}
	else
	{
		if(strcmp(in, "M") == 0)
			strcpy(out, "1110000");
		else if(strcmp(in, "!M") == 0)
			strcpy(out, "1110001");
		else if(strcmp(in, "-M") == 0)
			strcpy(out, "1110011");
		else if(strcmp(in, "M+1") == 0)
			strcpy(out, "1110111");
		else if(strcmp(in, "M-1") == 0)
			strcpy(out, "1110010");
		else if(strcmp(in, "D+M") == 0)
			strcpy(out, "1000010");
		else if(strcmp(in, "D-M") == 0)
			strcpy(out, "1010011");
		else if(strcmp(in, "M-D") == 0)
			strcpy(out, "1000111");
		else if(strcmp(in, "D&M") == 0)
			strcpy(out, "1000000");
		else if(strcmp(in, "D|M") == 0)
			strcpy(out, "1010101");
	}
}

//takes and address and returns binary string
void getBinAddress(char* in, char* out)
{
	int n = atoi(in);
	int i;
	for(i=14; i >= 0; i--)
	{
		if(n & 1)
			out[i] = '1';
		else
			out[i] = '0';
		n = n >> 1;
	}
	out[15] = '\0';
}

void getABinary(char* addr, char* out)
{
	out[0] = '0';
	getBinAddress(addr, out+1);
}

void getCBinary(char* dest, char* comp, char* jump, char* out)
{
	out[0] = out[1] = out[2] = '1';
	getBinComp(comp, out+3);
	getBinDest(dest, out+10);
	getBinJump(jump, out+13);
}

void getBinOut(struct ParsedCommand* p, char* out)
{
	if(p->ct == C_TYPE)
		getCBinary(p->dest, p->comp, p-> jump, out);
	else
		getABinary(p->memLocation, out);
}



