for dir in $(ls | grep lab_04)
do
    echo "DIR: $dir:\n"
    for c_file in $(ls | grep .c)
    do
        gcc -std=c99 -Werror -Wall -c c_file
    done

done