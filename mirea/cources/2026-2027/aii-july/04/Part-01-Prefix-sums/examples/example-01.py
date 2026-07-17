# Пример: сумма положительных чисел на отрезке.
# Читает массив и запросы [l, r] в единичной индексации.
# Для каждого запроса выводит сумму положительных элементов на отрезке.

n, q = map(int, input().split())
a = list(map(int, input().split()))

# pref_pos[i] хранит сумму положительных элементов среди первых i чисел.
pref_pos = [0] * (n + 1)
for i in range(n):
    pref_pos[i + 1] = pref_pos[i]
    if a[i] > 0:
        pref_pos[i + 1] += a[i]

for _ in range(q):
    l, r = map(int, input().split())
    l -= 1
    r -= 1
    # Сумма на отрезке берётся как разность двух префиксов.
    print(pref_pos[r + 1] - pref_pos[l])