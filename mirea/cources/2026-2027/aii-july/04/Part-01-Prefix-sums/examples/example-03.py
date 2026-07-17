# Пример: Python-аналог безопасного partial_sum.
# Ввод: n и массив чисел.
# Вывод: массив префиксных сумм длины n + 1.

n = int(input())
a = list(map(int, input().split()))

pref = [0] * (n + 1)
for i in range(n):
    pref[i + 1] = pref[i] + a[i]

print(*pref)