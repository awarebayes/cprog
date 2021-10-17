#! /usr/bin/sh

for dir in $(ls | grep lab_08)
do
    cd $dir
    echo "$dir:\n"
    for f in  ./**/*.c
    do
        code_checker $f
    done
    for f in ./**/*.h
    do
        code_checker $f
    done
    cd ..
done