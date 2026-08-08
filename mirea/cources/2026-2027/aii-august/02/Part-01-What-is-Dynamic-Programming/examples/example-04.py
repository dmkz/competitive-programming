def solve(i):
    if i == 0: return 0
    if ready[i]: return dp[i]
    # Кэшируем лучший результат после рекурсивного вычисления предшественников.
    dp[i] = a[i] + solve(i - 1)
    if i >= 2: dp[i] = max(dp[i], a[i] + solve(i - 2))
    ready[i] = True
    return dp[i]
# Читаем награды ступеней:
n = int(input())
a = [0] + list(map(int, input().split()))
dp = [0] * (n + 1)
ready = [False] * (n + 1)
print(solve(n))