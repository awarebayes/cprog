#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "test.c"

int main()
{
    test_strpbrk();
    test_strspn();
    test_strcspn();
    test_strchr();
    test_strrchr();
    return 0;
}