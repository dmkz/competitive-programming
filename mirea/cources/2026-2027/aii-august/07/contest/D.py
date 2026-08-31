def solve():
    # читаем данные. Для удобства сразу делаем так, чтобы количество столбцов было равно 2
    # для этого транспонируем матрицу при чтении, если это не так.
    n, m = map(int, input().split())
    a = [[0, 0] for _ in range(max(n,m))]
    if n <= m:
        assert n == 2
        for r in range(n):
            row = list(map(int, input().split()))
            for c in range(m):
                a[c][r] = row[c]
    else:
        assert m == 2
        for r in range(n):
            a[r] = list(map(int, input().split()))
    # теперь считаем динамику: dp[r][c] - максимальная сумма на пути из (1,1) в (r,c)
    n = max(n, m)
    inf = 10**18
    dp = [[-inf, -inf] for _ in range(n)]
    dp[0][0] = a[0][0] # стартовое число
    dp[0][1] = a[0][0] + a[0][1] # прямой переход вправо
    for i in range(1, n):
        # переход в клетку (i, 0):
        dp[i][0] = max(dp[i][0], dp[i-1][0] + a[i][0]) # сверху
        dp[i][0] = max(dp[i][0], dp[i-1][1] + a[i][0] + a[i][1]) # справа
        # переход в клетку (i, 1):
        dp[i][1] = max(dp[i][1], dp[i-1][1] + a[i][1]) # сверху
        dp[i][1] = max(dp[i][1], dp[i-1][0] + a[i][0] + a[i][1]) # слева
    # выводим ответ:
    print(dp[n-1][1])
tt = int(input())
for _ in range(tt):
    solve()