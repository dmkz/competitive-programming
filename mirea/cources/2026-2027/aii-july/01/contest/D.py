# Прочитаем массив чисел, скопируем его, отсортируем копию. Теперь для каждого
# элемента оригинального массива посчитаем, сколько элементов меньше него в
# отсортированной копии, с помощью бинарного поиска в отсортированном массиве.
from bisect import bisect_left

def solve():
    n = int(input())
    a = list(map(int, input().split()))
    b = sorted(a)
    for i in range(n):
        print(bisect_left(b, a[i]), end=' ')
    print()

tt = int(input())
for _ in range(tt):
    solve()