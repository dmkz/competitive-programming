# Пример: восстановление массива по известным префиксным суммам.
# Ввод: n и массив pref длины n + 1.
# Вывод: исходный массив a.

n = int(input())
pref = list(map(int, input().split()))

a = [0] * n
for i in range(n):
    a[i] = pref[i + 1] - pref[i]

print(*a)