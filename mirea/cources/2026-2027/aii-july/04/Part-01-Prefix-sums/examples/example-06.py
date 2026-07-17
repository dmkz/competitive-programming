# Пример: суффиксные суммы с индексацией позицией начала суффикса.
# Ввод: n и массив.
# Вывод: массив suff длины n + 1.

n = int(input())
a = list(map(int, input().split()))

suff = [0] * (n + 1)
for i in range(n - 1, -1, -1):
    suff[i] = suff[i + 1] + a[i]

print(*suff)