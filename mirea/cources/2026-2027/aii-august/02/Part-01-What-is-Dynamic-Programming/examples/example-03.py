# Читаем награды ступеней:
n = int(input())
a = [0] + list(map(int, input().split()))
# dp[i] — наибольшая сумма на маршруте до ступени i.
dp = [0] * (n + 1)
if n >= 1: dp[1] = a[1]
for i in range(2, n + 1):
    dp[i] = a[i] + max(dp[i - 1], dp[i - 2])
print(dp[n])