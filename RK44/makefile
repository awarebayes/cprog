main.exe: main.o list.o
	gcc -o main.exe main.o list.o

main.o: main.c list.c list.h
	gcc -c main.c -Wall

list.o: list.c list.h
	gcc -c list.c -Wall

.PHONY: run
run: main.exe
	./main.exe -f ./in.txt

