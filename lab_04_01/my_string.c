#pragma once

#include <stdio.h>

const char *my_strpbrk(const char *str1, const char *str2)
{
    const char *start_str2 = str2;
    const char *found = NULL;
    while (*str1 && !found)
    {
        while (*str2 && !found)
        {
            if (*str1 == *str2)
                found = str1;
                // return found
            str2++;
        }
        str1++;
        str2 = start_str2;
    }
    return found;
}

size_t my_strspn(const char *str1, const char *str2)
{
    size_t n = 0;
    const char *start_str2 = str2;
    int flag = 1;
    while (*str1 && flag)
    {
        flag = 0;
        while (*str2)
        {
            if (*str1 == *str2)
                flag = 1;
            str2++;
        }
        str1++;
        n++;
        str2 = start_str2;
    }
    return n - 1;
}

size_t my_strcspn(const char *str1, const char *str2)
{
    size_t n = 0;
    const char *start_str2 = str2;
    int flag = 0;
    while (*str1 && !flag)
    {
        while (*str2 && !flag)
        {
            if (*str1 == *str2)
                flag = 1;
            str2++;
        }
        str1++;
        n++;
        str2 = start_str2;
    }
    return n - 1;
}

const char *my_strchr(const char *str, int character)
{
    int flag = 1;
    while (*str && flag)
    {
        if (*str == (char)character)
            flag = 0;
        str++;
    }
    return (*str) ? (str - 1) : NULL;
}

const char *my_strrchr(const char *str, int character)
{
    int flag = 1;
    const char *strbegin = str;
    while (*str)
        str++;
    str--; 
    while (str >= strbegin && flag)
    {
        if (*str == (char)character)
            flag = 0;
        str--;
    }
    return (strbegin <= str) ? (str + 1) : NULL;
}
