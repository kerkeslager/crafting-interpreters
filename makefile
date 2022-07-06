all: main.o chunk.o debug.o memory.o
	gcc main.o chunk.o debug.o memory.o -o lox

main.o:
	gcc -I . -c main.c

chunk.o:
	gcc -I . -c chunk.c

debug.o:
	gcc -I . -c debug.c

memory.o:
	gcc -I . -c memory.c

clean:
	rm *.o
	rm lox
