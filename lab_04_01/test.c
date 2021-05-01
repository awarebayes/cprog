#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "my_string.c"

void test_strpbrk()
{
    char *str1 = "abcdeff123";
    char *str2 = "e";
    assert(strpbrk(str1, str2) == my_strpbrk(str1, str2));
    str2 = "ec";
    assert(strpbrk(str1, str2) == my_strpbrk(str1, str2));
    str2 = "32";
    assert(strpbrk(str1, str2) == my_strpbrk(str1, str2));
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
    char *str2 = "123asdvc";
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