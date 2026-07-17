# Пример: два слоя предобработки.
# Ввод: n, m, k, q; затем m отрезков и q запросов.
# Вывод: для каждого запроса число позиций, покрытых хотя бы k отрезками.

n, m, k, q = map(int, input().split())

# В массиве a накапливаем, где покрытие начинается и где заканчивается.
a = [0] * (n + 1)
for _ in range(m):
    l, r = map(int, input().split())
    l -= 1
    r -= 1
    a[l] += 1
    if r + 1 < n:
        a[r + 1] -= 1

# Строим бинарный массив good: хорошая ли позиция.
g = [0] * n
current = 0
for i in range(n):
    current += a[i]
    if current >= k:
        g[i] = 1

# Поверх good строим ещё одни префиксные суммы.
h = [0] * (n + 1)
for i in range(n):
    h[i + 1] = h[i] + g[i]

for _ in range(q):
    l, r = map(int, input().split())
    l -= 1
    r -= 1
    print(h[r + 1] - h[l])