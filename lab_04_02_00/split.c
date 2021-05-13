#include "split.h"
#include <stdio.h>
#include <string.h>

char *split_on = " ,;:-.!?";
#define NSPLITC 8 // N splitting characters

int split(char **words, char *s, int n, int *ec)
{
    if (*ec)
        return -1;
    *ec = 0;
    int just_splitted = 1; // Только что разделили, во 2 раз не надо
    int should_split = 0; // Нужно ли разделять
    int current_word = 0; // Индекс слова, которое мы сейчас обрабатываем
    int current_char = 0; // Индекс буквы в слове
    for (int i = 0; i <= n && !(*ec); i++)
    {
        should_split = 0;
        for (int j = 0; j < NSPLITC; j++)
        {
            if (s[i] == split_on[j])
                should_split = 1;
        }
        if ((should_split && !just_splitted) || (i == n && !just_splitted))
        {
            words[current_word][current_char] = '\0';
            current_word++;
            current_char = 0;
            just_splitted = 1;
        }
        else if (!should_split)
        {
            words[current_word][current_char] = s[i];
            current_char++;
            if (current_char >= 17)
                *ec = 3; // long word
            just_splitted = 0;
        }
    }
    return current_word;
}

void transform(size_t n, size_t m, char *mat, char **pa)
{
    for (size_t i = 0; i < n; i++)
        pa[i] = mat + m * i;
}