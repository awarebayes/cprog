#! /usr/bin/sh
gcc -std=c99 -Wall -Werror -c futil.c
gcc -std=c99 -Wall -Werror -c main.c
gcc -o main main.o futil.o