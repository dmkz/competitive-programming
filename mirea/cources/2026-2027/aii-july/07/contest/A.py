# Для каждого x[j] нужно найти минимальный i такой, что x[j] < a[1] + a[2] + ... + a[i].
# Этот номер i будет равен первой доске, которую мы не сможем пробить. Чтобы быстро искать
# данный индекс, построим вектор префиксных-сумм и сделаем бинарный поиск в нём.
from bisect import bisect_right


def solve():
    # читаем массив:
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    # считаем префиксные суммы:
    s = [0]
    for value in a:
        s.append(s[-1] + value)
    # отвечаем на запросы: для заданного x нужно найти ближайший s[i] > x
    # используем для этого бинарный поиск (bisect_right)
    for x in map(int, input().split()):
        print(bisect_right(s, x) - 1, end=' ')
    print()


tt = int(input())
while tt > 0:
    solve()
    tt -= 1