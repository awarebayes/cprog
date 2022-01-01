main.exe: main.o list.o
	gcc -o main.exe main.o list.o -g -DDEBUG

main.o: main.c list.c list.h
	gcc -c main.c -Wall -g -DDEBUG

list.o: list.c list.h
	gcc -c list.c -Wall -g -DDEBUG

all: main.exe

.PHONY: run
run: main.exe
	./main.exe -f ./in.txt

