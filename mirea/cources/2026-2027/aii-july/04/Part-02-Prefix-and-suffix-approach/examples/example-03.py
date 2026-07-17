# Пример: суффиксные суммы.
# Ввод: n и массив чисел.
# Вывод: массив суффиксных сумм длины n + 1.

n = int(input())
a = list(map(int, input().split()))

suf = [0] * (n + 1)
for i in range(n - 1, -1, -1):
    suf[i] = suf[i + 1] + a[i]

print(*suf)