#! /usr/bin/sh
for file in *.c
do
    gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c "$file"
done

if gcc -o main $(echo *.o | cut -f1 -d-)
then
    echo "🚀 Build succsessful!"
else 
    echo "🤔 Build failed!"
fi