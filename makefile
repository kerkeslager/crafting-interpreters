all: clean main.o chunk.o debug.o memory.o value.o vm.o
	gcc main.o chunk.o debug.o memory.o value.o vm.o -o lox

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

vm.o:
	gcc -I . -c vm.c

clean:
	rm -f *.o
	rm -f lox
