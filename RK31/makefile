main.exe: main.o matrix.o
	gcc -o main.exe main.o matrix.o

main.o: main.c matrix.c matrix.h
	gcc -c main.c -Wall

matrix.o: matrix.c matrix.h
	gcc -c matrix.c -Wall

.PHONY: run
run: main.exe
	./main.exe ./in.txt 1
