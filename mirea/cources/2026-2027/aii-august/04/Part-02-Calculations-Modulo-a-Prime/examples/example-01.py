mod = 10 ** 9 + 7
n, k = map(int, input().split())
# ways[i][j] хранит число путей после i шагов вниз и j шагов вправо.
ways = [[0] * (k + 1) for i in range(n + 1)]
ways[0][0] = 1
# В каждую клетку приходим из клетки сверху или слева.
for i in range(n + 1):
	for j in range(k + 1):
		if i == 0 and j == 0: continue
		fromTop = 0 if i == 0 else ways[i - 1][j]
		fromLeft = 0 if j == 0 else ways[i][j - 1]
		ways[i][j] = (fromTop + fromLeft) % mod
print(ways[n][k])