# Пример: Python-аналог exclusive_scan.
# Ввод: n и массив чисел.
# Вывод: массив префиксных сумм длины n + 1.

n = int(input())
a = list(map(int, input().split()))

extended = a + [0]
pref = [0] * (n + 1)
current = 0
for i in range(n + 1):
    pref[i] = current
    current += extended[i]

print(*pref)