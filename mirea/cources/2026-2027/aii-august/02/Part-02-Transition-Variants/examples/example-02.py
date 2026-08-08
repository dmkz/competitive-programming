# Читаем высоты платформ:
n = int(input())
h = list(map(int, input().split()))
# dp[i] — наименьшая цена, с которой лягушка приходит на i-ю платформу.
inf = 10 ** 30
dp = [inf] * n
dp[0] = 0
for i in range(1, n):
    dp[i] = dp[i - 1] + abs(h[i] - h[i - 1])
    if i >= 2: dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]))
# Последняя ячейка содержит цену пути до последней платформы.
print(dp[-1])