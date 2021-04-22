#! /usr/bin/bash

cd $1
gcc -std=c99 -Werror -Wall -lm ./main.c -o ./main.exe
cd ..

for i in $(seq 1000)
do
    python ./scripts/fuzz/generate.py > ./scripts/fuzz/input.txt
    
    if ! diff -b -B <(python ./scripts/fuzz/solve.py < ./scripts/fuzz/input.txt) <(./$1/main.exe < ./scripts/fuzz/input.txt) > /dev/null
    then
        echo "_____________"
        echo "$TEST failed:"
        diff -b -B <(python ./scripts/fuzz/solve.py < ./scripts/fuzz/input.txt) <(./$1/main.exe < ./scripts/fuzz/input.txt) 
        echo "_____________"
        exit
    fi
done;