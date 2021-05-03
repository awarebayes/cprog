#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "strings.h"
#include "util.h"

int main()
{
    int ec = ok;
    char str[MSTRLEN];
    char result[MSTRLEN] = { '\0' };
    char *end = result;
    int remaining; // сколько слов осталось после удаления

    char words[MWORDS][MWORDLEN];
    char *pa[MWORDS];
    transform(MWORDS, MWORDLEN, *words, pa); 

    read_line(str, MSTRLEN, &ec);
    if (!ec)
    {   
        char *line_start = str;
        int mwlen = max_word_len(line_start);
        if (mwlen > MWORDLEN)
            ec = long_word;
        else
        {
            int n_words;
            n_words = split_string_to_words(pa, str);

            remaining = delete_matching_last_word(pa, n_words);
            if (remaining == 0)
                ec = no_words_remaining;
            else
            {
                solve(n_words, pa, end);
                result[strlen(result) - 1] = '\0';
                printf("Result: %s\n", result); 
            }
        }
    }
    print_error(ec);
    return ec;
}


