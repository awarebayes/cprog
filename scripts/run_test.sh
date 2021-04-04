#! /usr/bin/bash
cd $1
gcc -std=c99 -Werror -Wall -lm ./main.c -o ./main
cd ./func_tests
for TEST in $(ls | grep _in.txt | sed 's/_[^_]*//2g')
do
    if [ -s ${TEST}_in.txt ]
    then
        if ! diff -b -B ./${TEST}_out.txt <(../main < ./${TEST}_in.txt)
        then
            echo "_____________"
            echo "$TEST failed:"
            diff -y -b -B ./${TEST}_out.txt <(../main < ./${TEST}_in.txt)
            echo "_____________"
        fi
    fi
done