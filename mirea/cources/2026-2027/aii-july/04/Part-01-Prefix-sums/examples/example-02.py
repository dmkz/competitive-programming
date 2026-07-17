# Пример: базовые префиксные суммы и ответы на запросы суммы на отрезке.
# Ввод: n, массив, q, затем q запросов [l, r] в единичной индексации.
# Вывод: сумма на каждом отрезке.

n = int(input())
a = list(map(int, input().split()))

# pref[i] хранит сумму первых i элементов.
pref = [0] * (n + 1)
for i in range(n):
    pref[i + 1] = pref[i] + a[i]

q = int(input())
for _ in range(q):
    l, r = map(int, input().split())
    l -= 1
    r -= 1
    print(pref[r + 1] - pref[l])