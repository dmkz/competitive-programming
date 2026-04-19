# жадные алгоритмы, сортировка
import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    # операции позволяют переставлять все 2*n элементов как угодно
    # например, если мы хотим переставить a[i] и b[j], то делаем:
    # swap(a[i], a[j]) + swap(a[j], b[j]) + swap(a[i], a[j])
    # поэтому отсортируем все 2*n чисел и будем комбинировать в пары
    # в порядке убывания значений элементов
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    for x in b:
        a.append(x)
    a.sort()
    res = 0
    for i in range(0, 2 * n, 2):
        res += a[i] * a[i + 1]
    print(res)