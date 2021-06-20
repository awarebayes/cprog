"""
/*
 * 2.3
 * Задача 4 лабы 3
 * 0. Найти и вывести на экран минимальное нечётное
 * число, расположенное под главной диагональю. 
 * Написал: Щербина Михаил
 */
"""

import random
min_even = None
n = 10
arr = [[random.randint(-10, 10) for r in range(n)] for j in range(n)]


for i in range(n):
    for j in range(n):
        print(arr[i][j], end=' ')
    print()


for i in range(n):
    for j in range(n):
        if i > j and arr[i][j] % 2 == 1:
            if min_even is None:
                min_even = arr[i][j]
            else:
                min_even = min(min_even, arr[i][j])

print(min_even)