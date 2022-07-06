all: clean main.o chunk.o debug.o memory.o value.o
	gcc main.o chunk.o debug.o memory.o value.o -o lox

main.o:
	gcc -I . -c main.c

chunk.o:
	gcc -I . -c chunk.c

debug.o:
	gcc -I . -c debug.c

memory.o:
	gcc -I . -c memory.c

value.o:
	gcc -I . -c value.c

clean:
	rm *.o
	rm lox
