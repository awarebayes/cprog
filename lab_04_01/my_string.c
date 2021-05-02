#pragma once

#include <stdio.h>


const char *my_strchr(const char *str, int character);

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
    if (*str1 == '\0' || *str2 == '\0')
        return n;

    while (*str1 && my_strchr(str2, *str1++))
        n++;
    return n;
}

size_t my_strcspn(const char *str1, const char *str2)
{
    size_t n = 0;
    if (*str1 == '\0' || *str2 == '\0')
        return n;
    while (*str1 && !(my_strchr(str2, *str1++)))
        n++;
    return n;
}

const char *my_strchr(const char *str, int character)
{
    const char *result;
    int flag = 1;

    if (!(*str) && character == 0)
        return str;

    while (*str && flag)
    {
        if (*str == (char)character)
            flag = 0;
        str++;
    }
    if (*(str - 1) == (char)character)
        result = str - 1;
    else
    {
        if (character) // charachter не \0, возможно возвращаем null
            result = (*str) ? str : NULL;
        else
            result = str; // если character \0 то конец строки
    }
    return result;
}

const char *my_strrchr(const char *str, int character)
{
    int flag = 1;
    const char *strbegin = str;
    const char *result;

    while (*str)
        str++;

    if (character == 0)
        result = str;
    else
    {
        str--; 
        while (str >= strbegin && flag)
        {
            if (*str == (char)character)
                flag = 0;
            str--;
        }

        if (*(str + 1) == (char)character)
            result = str + 1;
        else
            result = (strbegin <= str) ? (str + 1) : NULL;
    }

    return result;
}
