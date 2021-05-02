#include <stdio.h>

#define MWORDLEN 32
#define MWORDS 128
#define MSTRLEN 256
#define DELIM " ,;:-.!?"

int split_string_to_words(char **words, char *str)
{
    int cur_word = 0;
    char *pch = strtok(str, DELIM);

    while (pch != NULL)
    {
        strcpy(words[cur_word], pch);
        cur_word++;
        pch = strtok(NULL, DELIM);
    }
    return cur_word;
}

int delete_matching_last_word(char **words, int n)
{
    char *last_word = words[n - 1];
    int remaining = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(words[i], last_word) == 0)
            words[i][0] = '\0';
        else
            remaining += 1;
    }
    return remaining;
}

void delete_letters_matching_first(char *word)
{
    char new_word_arr[MWORDLEN];
    char *new_word = new_word_arr;
    char *word_start = word;

    if (!isalpha(word[0]))
        return; 
    
    char first_letter = word[0];
    *(new_word++) = first_letter;
    while (*word)
    {
        if (*word != first_letter)
            *(new_word++) = *(word);
        word++;
    }
    
    *(new_word++) = '\0';

    strcpy(word_start, new_word_arr);
}

void solve(int n_words, char **pa, char *end)
{
    for (int i = n_words - 1; i >= 0; i--)
    {
        if (pa[i][0])
        {
            delete_letters_matching_first(pa[i]);
            end = strcat(end, pa[i]);
            end = strcat(end, " ");
        }
    }
}

int max_word_len(char *str)
{
    int max_len = 0;
    int current_len = 0;
    while (*str)
    {
        if (strchr(DELIM, *str) != NULL)
        {
            if (max_len < current_len)
                max_len = current_len;
            current_len = 0;
        }
        else
            current_len++;
        str++;
    }
    return max_len;
}