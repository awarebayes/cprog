#! /usr/bin/sh
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c main.c
gcc -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c movie.c
gcc -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c movie_arr.c
gcc -o main main.o movie.o movie_arr.o

if [ $? -eq 0 ]
then
    echo "🚀 Build succsessful!"
else 
    echo "🤔 Build failed!"
fi