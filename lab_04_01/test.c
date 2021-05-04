#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "my_string.h"
#include "test.h"

char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK,.:;!12345";
    if (size) 
    {
        --size;
        for (size_t n = 0; n < size; n++) 
        {
            int key = rand() % (int) (sizeof(charset) - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void fuzz()
{
    int str1_len = 100;
    int str2_len = 100;
    char str1[str1_len];
    char str2[str2_len];

    for (size_t i = 0; i < 1000000000; i++) 
    {
        str1_len = rand() % 100;
        str2_len = rand() % 100;
        // char c = rand() % 128;
        rand_string(str1, str1_len);
        rand_string(str2, str2_len);
        if (strcspn(str1, str2) != strcspn(str1, str2))
        {
            printf("Fuzzing failed:\n");
            printf("s1: '%s'\n", str1);
            printf("s2: '%s'\n", str2);
            // printf("s2: %c (%d)\n", c, (int)c);
            printf("std, %zu\n", strcspn(str1, str2));
            printf("my , %zu\n", my_strcspn(str1, str2));
            printf("___________________\n");
            exit(1);
        }
    }
}

void test_strspn()
{
    char *str1 = "abcdeff123";
    char *str2 = "abc";
    assert(strspn(str1, str2) == my_strspn(str1, str2));
    str2 = "def";
    assert(strspn(str1, str2) == my_strspn(str1, str2));
    str2 = "abc23453";
    assert(strspn(str1, str2) == my_strspn(str1, str2));
}

void test_strcspn()
{
    char *str1 = "abcdeff123";
    char *str2 = "\0";
    size_t s1 = strcspn(str1, str2);
    size_t s2 = my_strcspn(str1, str2);
    assert (s1 == s2);
    assert(strcspn(str1, str2) == my_strcspn(str1, str2));
    str2 = "34213def";
    assert(strcspn(str1, str2) == my_strcspn(str1, str2));
    str2 = "f";
    assert(strcspn(str1, str2) == my_strcspn(str1, str2));
}

void test_strchr()
{
    char *str1 = "abcdeff123";
    char str2 = 'a';
    assert(strchr(str1, str2) == my_strchr(str1, str2));
    str2 = 'f';
    assert(strchr(str1, str2) == my_strchr(str1, str2));
    str2 = '*';
    assert(strchr(str1, str2) == my_strchr(str1, str2));
}

void test_strrchr()
{
    char *str1 = "abcdeff123";
    char str2 = '1';
    
    assert(strrchr(str1, str2) == my_strrchr(str1, str2));
    str2 = 'f';
    assert(strrchr(str1, str2) == my_strrchr(str1, str2));
    str2 = '*';
    assert(strrchr(str1, str2) == my_strrchr(str1, str2));
}