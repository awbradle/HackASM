#include "main.h" 

struct list 
{
	struct list* next;
	char* line;
};

int main(int argc, char* argv[])
{
	FILE* in;
	FILE* out;
	char* inLine = NULL;
	char* cleanLine;
	unsigned long inLen = 0;
	char* outName = NULL;
	struct list* head = NULL;
	struct list* curr = NULL;
	struct list* prev = NULL;
	struct ParsedCommand* p;
	
	if(argc != 2)
	{
		fprintf(stderr, "usage: hasm <input>\n");
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	if(in == NULL)
	{
		fprintf(stderr, "error: cannot open file '%s'\n",argv[1]);
		exit(1);
	}
	inLen = strlen(argv[1]);
	outName = malloc(inLen+2);
	strcpy(outName, argv[1]);
	strcpy(outName+inLen-3, "hack");
	out = fopen(outName, "w");
	if(out == NULL)
	{
		fprintf(stderr, "error: cannot open file '%s'\n",outName);
		exit(1);
	}
	int charRead = 0;
	inLen = 0;
	while((charRead = getline(&inLine, &inLen, in)) > 0)
	{
		curr = (struct list*) malloc(sizeof(struct list));
		cleanLine = getCleanLine(inLine);
		printf("%s, %d\n", cleanLine, strlen(cleanLine));
		if(cleanLine == NULL || curr == NULL)
		{
			fprintf(stderr, "error: malloc failed\n");
			exit(1);
		}
		
		(curr->line) = cleanLine;
		if (head == NULL)
			head = curr;
		if (prev != NULL)
			prev->next = curr;
		prev = curr;
	}
	while(head != NULL && (strlen(head->line) == 0))
		head = head->next;
	char binOut[17];
	while(head != NULL)
	{
		//printf( "%s", (head->line));
		p = getParsedCommand(head->line);
		getBinOut(p, binOut);
		fprintf(out, "%s\n", binOut);
		curr = head;
		head = head->next;
		while(head != NULL && (strlen(head->line) == 0))
			head = head->next;
		free(curr->line);
		free(curr);
	}
	
	printf("%s %s\n", argv[1], outName);
	fclose(in);
	fclose(out);
	return 0;
}