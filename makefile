all: clean main.o chunk.o compiler.o debug.o memory.o scanner.o value.o vm.o
	gcc main.o chunk.o compiler.o debug.o memory.o scanner.o value.o vm.o -o lox

main.o:
	gcc -I . -c main.c

chunk.o:
	gcc -I . -c chunk.c

compiler.o: scanner.o
	gcc -I . -c compiler.c

debug.o:
	gcc -I . -c debug.c

memory.o:
	gcc -I . -c memory.c

scanner.o:
	gcc -I . -c scanner.c

value.o:
	gcc -I . -c value.c

vm.o:
	gcc -I . -c vm.c

clean:
	rm -f *.o
	rm -f lox
