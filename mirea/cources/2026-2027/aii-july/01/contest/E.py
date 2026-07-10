# Нужно посчитать количество пар: a[i] + a[j] <= s. Для этого зафиксируем a[j] и
# перенесём направо. Тогда требуется посчитать количество элементов a[i]:
# a[i] <= (s - a[j]) на полуинтервале [0, j) для каждого a[j].

from bisect import bisect_right

def solve():
    n, s = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()
    answ = 0
    for j in range(n):
        answ += bisect_right(a, s - a[j], 0, j)
    print(answ)

tt = int(input())
for _ in range(tt):
    solve()