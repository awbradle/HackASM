hasm: main.c code.c list.c parser.c
	gcc -Wall -o hasm main.c code.c list.c parser.c
clean:
	rm -f hasm code.o list.o parser.o
