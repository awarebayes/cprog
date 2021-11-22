#! /usr/bin/sh

python ../temp.py > ./input.txt
gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm -pg -O0 ./main.c -o ./main
./main < input.txt
gprof -b main > report.txt
clear
cat report.txt