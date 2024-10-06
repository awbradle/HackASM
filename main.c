#include "main.h" 

struct list* inputHead = NULL;

int main(int argc, char* argv[])
{
	FILE* in;
	FILE* out;
	if(argc != 2)
	{
		fprintf(stderr, "usage: hasm <input>\n");
		exit(1);
	}
	handleFileIO(&in, &out, argv[1]);
	cleanInput(in, out); 
	fclose(in);
	writeOut(out);
	fclose(out);
	cleanupParserSymbolTable();
	return 0;
}

//Open input and out files
void handleFileIO(FILE** in, FILE** out, char* inName)
{	
	unsigned long inLen = 0;
	char* outName = NULL;
	*in = fopen(inName, "r");
	if(*in == NULL)
	{
		fprintf(stderr, "error: cannot open file '%s'\n",inName);
		exit(1);
	}
	inLen = strlen(inName);
	outName = malloc(inLen+2);
	strcpy(outName, inName);
	strcpy(outName+inLen-3, "hack");
	*out = fopen(outName, "w");
	if(*out == NULL)
	{
		fprintf(stderr, "error: cannot open file '%s'\n",outName);
		exit(1);
	}
}

//Read and read input file and perform first pass to create a symbol table
void cleanInput(FILE* in, FILE* out)
{	
	char* inLine = NULL;
	char* cleanLine;
	int charRead = 0;
	int lineCount = 0;
	unsigned long inLen = 0;
	struct list* curr = NULL;
	struct list* prev = NULL;
	setupParserSymbolTable();
	while((charRead = getline(&inLine, &inLen, in)) > 0)
	{
		curr = (struct list*) malloc(sizeof(struct list));
		cleanLine = getCleanLine(inLine);
		if(cleanLine == NULL || curr == NULL)
		{
			fprintf(stderr, "error: malloc failed\n");
			exit(1);
		}
		if(cleanLine != NULL && strlen(cleanLine) > 0)
		{
			if(getCommandType(cleanLine) == L_TYPE)
			{
				processLabel(cleanLine,lineCount);
				free(cleanLine);
			}
			else
			{
				(curr->line) = cleanLine;
				if (inputHead == NULL)
					inputHead = curr;
				if (prev != NULL)
					prev->next = curr;
				prev = curr;
				lineCount++;
			}
		}
		else
			free(cleanLine);
	}
}

//Write out binary file
void writeOut(FILE* out)
{
	char binOut[17];
	struct list* curr = NULL;
	struct ParsedCommand* p;
	while(inputHead != NULL)
	{
		p = getParsedCommand(inputHead->line);
		getBinOut(p, binOut);
		fprintf(out, "%s\n", binOut);
		curr = inputHead;
		inputHead = inputHead->next;
		while(inputHead != NULL && (strlen(inputHead->line) == 0))
			inputHead = inputHead->next;
		free(curr->line);
		free(curr);
		free(p);
	}
}
