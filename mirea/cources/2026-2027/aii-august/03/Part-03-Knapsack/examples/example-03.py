# Считываем предметы и вместимость рюкзака:
n, c = map(int, input().split())
w, v = [0] * (n + 1), [0] * (n + 1)
for i in range(1, n + 1):
    w[i], v[i] = map(int, input().split())
# Сохраняем все строки и координаты предка для каждого оптимального состояния.
dp = [[0] * (c + 1) for i in range(n + 1)]
parent = [[(-1, -1)] * (c + 1) for i in range(n + 1)]
for i in range(1, n + 1):
    for x in range(c + 1):
        # Сначала рассматриваем вариант, в котором предмет i не входит в набор.
        dp[i][x] = dp[i - 1][x]
        parent[i][x] = i - 1, x
        # Если предмет i улучшает ответ, переходим из состояния с вместимостью x - w[i].
        if w[i] <= x and dp[i - 1][x - w[i]] + v[i] > dp[i][x]:
            dp[i][x] = dp[i - 1][x - w[i]] + v[i]
            parent[i][x] = i - 1, x - w[i]
# Восстанавливаем ответ, переходя по массиву parent от оптимального состояния к нулевой строке.
answ = []
i, x = n, c
while i > 0:
    prevI, prevX = parent[i][x]
    # Если при переходе уменьшилась вторая координата, предмет i вошёл в набор.
    if prevX != x:
        answ.append(i)
    i, x = prevI, prevX
# Индексы предметов получены в обратном порядке.
answ.reverse()
print(dp[n][c])
print(*answ)