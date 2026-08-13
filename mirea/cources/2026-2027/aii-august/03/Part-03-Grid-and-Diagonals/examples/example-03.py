# Считываем проходимость и значения клеток:
n, m = map(int, input().split())
cells = [input() for i in range(n)]
a = [list(map(int, input().split())) for i in range(n)]
def setmax(a, index, value):
    # Заменяем элемент, только если кандидат его улучшает.
    if a[index] < value: a[index] = value
# Номер диагонали i + j задаёт порядок обработки состояний.
inf = 10 ** 30
dp = [[-inf] * m for i in range(n)]
# Путь может начинаться только в проходимой верхней левой клетке.
if cells[0][0] == '.': dp[0][0] = a[0][0]
for d in range(n + m - 1):
    # На диагонали d перебираем только клетки, лежащие внутри сетки.
    low = max(0, d - m + 1)
    high = min(n - 1, d)
    for i in range(low, high + 1):
        j = d - i
        # Из недостижимой клетки продолжить путь нельзя.
        if dp[i][j] == -inf: continue
        # После шага вниз строка увеличивается на один.
        if i + 1 < n and cells[i + 1][j] == '.':
            setmax(dp[i + 1], j, dp[i][j] + a[i + 1][j])
        # После шага вправо столбец увеличивается на один.
        if j + 1 < m and cells[i][j + 1] == '.':
            setmax(dp[i], j + 1, dp[i][j] + a[i][j + 1])
if dp[n - 1][m - 1] == -inf: print('IMPOSSIBLE')
else: print(dp[n - 1][m - 1])