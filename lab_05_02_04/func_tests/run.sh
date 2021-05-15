#! /usr/bin/bash

for TEST in $(ls | grep _in.txt | sed 's/_[^_]*//2g')
do
    if ! diff ./${TEST}_out.txt <(../main ./${TEST}_in.txt) > /dev/null
    then
        echo "_____________"
        echo "$TEST failed:"
        diff -y ./${TEST}_out.txt <(../main ./${TEST}_in.txt)
        echo "_____________"
    fi
done