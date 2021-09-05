#! /usr/bin/sh

for dir in $(ls | grep lab_06)
do
    cd $dir
    echo "$dir:\n"
    code_checker main.c
    cd ..
done