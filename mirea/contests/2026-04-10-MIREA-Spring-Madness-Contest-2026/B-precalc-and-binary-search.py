# предподсчёт, бинарный поиск в массиве
import sys
import bisect

input = sys.stdin.readline

# предподсчитаем все ответы:
a = [0, 1]
for i in range(1, 1_000_001):
    a.append(a[-1] + 6 * i)

# ответим на все запросы:
t = int(input())
for _ in range(t):
    # находим нужное t бинарным поиском:
    n = int(input())
    print(bisect.bisect_left(a, n))