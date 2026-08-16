mod = 10 ** 9 + 7
n, k = map(int, input().split())
# ways[i][j] хранит число путей после i шагов вниз и j шагов вправо.
ways = [[0] * (k + 1) for i in range(n + 1)]
ways[0][0] = 1
# В каждую клетку приходим из клетки сверху или слева.
for i in range(n + 1):
	for j in range(k + 1):
		if i == 0 and j == 0: continue
		fromTop, fromLeft = 0, 0
		if i > 0: fromTop = ways[i - 1][j]
		if j > 0: fromLeft = ways[i][j - 1]
		answ = fromTop + fromLeft
		if answ >= mod: answ -= mod
		ways[i][j] = answ
print(ways[n][k])