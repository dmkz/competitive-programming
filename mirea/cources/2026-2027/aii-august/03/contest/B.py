inf = 1 << 60
def solve():
    # читаем данные:
    n = int(input())
    a = list(map(int, input().split()))
    # считаем динамику: dp[i][k] -> максимальная сумма, с которой мы пришли в i-ю ступеньку,
    # где текущая серия взятых положительных чисел равна k.
    dp = [[-inf] * 3 for _ in range(n)]
    # инициализация динамики:
    if a[0] < 0:
        dp[0][0] = a[0]
    else:
        assert a[0] > 0
        dp[0][1] = a[0]
    for i in range(1, n):
        if a[i] < 0:  # отрицательное число прерывает серию
            for k in range(3):
                # прыжок на 1:
                if i - 1 >= 0:
                    dp[i][0] = max(dp[i][0], a[i] + dp[i - 1][k])
                # прежок на 2:
                if i - 2 >= 0:
                    dp[i][0] = max(dp[i][0], a[i] + dp[i - 2][k])
        elif a[i] > 0:  # положительное число продолжает серию
            for k in range(1, 3):
                # прыжок на 1:
                if i - 1 >= 0:
                    dp[i][k] = max(dp[i][k], a[i] + dp[i - 1][k - 1])
                # прыжок на 2:
                if i - 2 >= 0:
                    dp[i][k] = max(dp[i][k], a[i] + dp[i - 2][k - 1])
    # выводим ответ:
    answ = max(dp[n - 1])
    minPossibleAnswer = n * min(a)
    if answ < minPossibleAnswer:
        print(0)
    else:
        print(1, answ)

tt = int(input())
while tt > 0:
    solve()
    tt -= 1