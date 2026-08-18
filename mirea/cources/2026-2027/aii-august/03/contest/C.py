inf = 1 << 60
def solve():
    # читаем данные:
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    # сортируем участников по возрастанию их результатов:
    a.sort()
    # делим участников на группы
    dp = [[inf] * (k + 1) for _ in range(n + 1)]
    dp[0][0] = 0
    for i in range(n):
        for sz in range(2, 5):
            j = i - sz + 1
            if j < 0:
                continue
            # группа [j, i] стоимостью a[i] - a[j]
            for wasGroups in range(k):
                dp[i + 1][wasGroups + 1] = min(
                    dp[i + 1][wasGroups + 1],
                    dp[j][wasGroups] + a[i] - a[j]
                )
    # выводим ответ:
    print(dp[n][k])

tt = int(input())
while tt > 0:
    solve()
    tt -= 1