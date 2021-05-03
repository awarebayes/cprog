#pragma once
#include <stdio.h>

char *rand_string(char *str, size_t size);
void fuzz();
void test_strspn();
void test_strcspn();
void test_strchr();
void test_strrchr();