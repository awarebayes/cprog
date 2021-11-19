#! /usr/bin/bash

for TEST in $(ls | grep _in.txt | sed 's/_[^_]*//2g')
do
    if [ -s ${TEST}_in.txt ]
    then
        if [[ $TEST == neg_* ]]
        then
            if ../app.exe < ./${TEST}_in.txt
            then
                echo "negative ${TEST}_in.txt returned code 0"
                exit 1
            fi
        fi
        if [[ $TEST == pos_* ]]
        then
            if ! ../app.exe < ./${TEST}_in.txt
            then
                echo "positive ${TEST}_in.txt returned $?"
                exit 1
            fi
        fi
        if ! diff  --strip-trailing-cr  ./${TEST}_out.txt <(../app.exe < ./${TEST}_in.txt) > /dev/null
        then
            echo "_____________"
            echo "$TEST failed:"
            diff  --strip-trailing-cr  -y ./${TEST}_out.txt <(../app.exe < ./${TEST}_in.txt)
            echo "_____________"
            exit 1
        fi
    fi
done

echo "Tests passed!"