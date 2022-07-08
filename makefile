all: clean main.o chunk.o compiler.o debug.o memory.o object.o scanner.o value.o vm.o
	gcc obj/{chunk,compiler,debug,main,memory,object,scanner,value,vm}.o -o lox

main.o: obj
	gcc -I . -c main.c -o obj/main.o

chunk.o: obj
	gcc -I . -c chunk.c -o obj/chunk.o

compiler.o: obj
	gcc -I . -c compiler.c -o obj/compiler.o

debug.o: obj
	gcc -I . -c debug.c -o obj/debug.o

memory.o: obj
	gcc -I . -c memory.c -o obj/memory.o

object.o: obj
	gcc -I . -c object.c -o obj/object.o

scanner.o: obj
	gcc -I . -c scanner.c -o obj/scanner.o

value.o: obj
	gcc -I . -c value.c -o obj/value.o

vm.o: obj
	gcc -I . -c vm.c -o obj/vm.o

obj:
	mkdir -p obj

clean:
	rm -rf obj
	rm -f lox
