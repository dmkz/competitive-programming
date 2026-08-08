# Читаем награды и строку доступности клеток.
n = int(input())
a = list(map(int, input().split()))
cells = input()
inf = 10 ** 30
dp = [-inf] * n
# В первой клетке маршрут состоит только из неё самой.
if cells[0] == '.': dp[0] = a[0]
for i in range(1, n):
    if cells[i] == '.':
        # Последний прыжок мог быть только из одной из двух предыдущих клеток.
        best = dp[i - 1]
        if i >= 2: best = max(best, dp[i - 2])
        if best != -inf: dp[i] = best + a[i]
if dp[-1] == -inf: print(-1)
else: print(dp[-1])