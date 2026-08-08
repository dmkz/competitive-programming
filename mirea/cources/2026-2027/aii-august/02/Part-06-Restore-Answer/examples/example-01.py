# Читаем награды и строку доступности клеток:
n = int(input())
a = list(map(int, input().split()))
cells = input()
# Инициализируем те же состояния, что в задаче из предыдущей части:
inf = 10 ** 30
dp = [-inf] * n
parent = [-1] * n
if cells[0] == '.': dp[0] = a[0]
# Вычисляем тот же переход и сохраняем выбранного предка:
for i in range(1, n):
    if cells[i] == '.':
        # При равенстве оставляем прыжок на одну клетку, как в исходной динамике.
        prev = i - 1
        if i >= 2 and dp[i - 2] > dp[prev]: prev = i - 2
        if dp[prev] != -inf:
            # Значение и выбранное ребро перехода обновляются вместе.
            dp[i] = dp[prev] + a[i]
            parent[i] = prev
# Выводим -1 или восстанавливаем маршрут по предкам:
if dp[-1] == -inf:
    print(-1)
else:
    # Идём по сохранённым предкам и разворачиваем маршрут.
    path = []
    i = n - 1
    while i != -1:
        path.append(i + 1)
        i = parent[i]
    path.reverse()
    print(dp[-1])
    print(len(path))
    print(*path)