# Считываем проходимость и значения клеток:
n, m = map(int, input().split())
cells = [input() for i in range(n)]
a = [list(map(int, input().split())) for i in range(n)]
def setmax(a, index, value):
    # Заменяем элемент, только если кандидат его улучшает.
    if a[index] < value: a[index] = value
# dp[i][j] хранит наибольшую сумму на пути до клетки (i, j), а диагонали задают порядок обхода.
inf = 10 ** 30
dp = [[-inf] * m for i in range(n)]
# Путь может начинаться только в проходимой верхней левой клетке.
if cells[0][0] == '.': dp[0][0] = a[0][0]
# Перечисляем четыре разрешённых хода коня.
di = [2, 1, -1, 2]
dj = [1, 2, 2, -1]
for d in range(n + m - 1):
    # На диагонали d перебираем только клетки, лежащие внутри сетки.
    low = max(0, d - m + 1)
    high = min(n - 1, d)
    for i in range(low, high + 1):
        j = d - i
        # Из недостижимой клетки продолжить путь нельзя.
        if dp[i][j] == -inf: continue
        # Каждый ход ведёт на диагональ с большим номером.
        for move in range(4):
            ni, nj = i + di[move], j + dj[move]
            # Обновляем состояние только для проходимой клетки внутри сетки.
            if 0 <= ni < n and 0 <= nj < m and cells[ni][nj] == '.':
                setmax(dp[ni], nj, dp[i][j] + a[ni][nj])
if dp[n - 1][m - 1] == -inf: print('IMPOSSIBLE')
else: print(dp[n - 1][m - 1])