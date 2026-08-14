# На ступеньку i мы можем попасть только из ступенек от left[i] до right[i]. Значит, формула
# перехода суммирует независимые способы добраться до них:
# dp[i] = dp[l] + dp[l+1] + ... + dp[r].
# Чтобы вычислять сумму быстро, нам нужно хранить префиксные суммы поверх ответов динамики.
# Теперь считаем dp[i] = pref[r+1] - pref[l], а затем обновляем префиксные суммы вот так:
# pref[i+1] = dp[i] + pref[i]. Работаем с остатками по простому модулю 10^9+7.
mod = 10 ** 9 + 7
def solve():
    # читаем данные:
    n = int(input())
    s = input()
    left = [0] + list(map(int, input().split()))
    right = [0] + list(map(int, input().split()))
    for i in range(1, n):
        left[i] -= 1
    for i in range(1, n):
        right[i] -= 1
    # считаем динамику и префиксные суммы для неё:
    dp = [0] * n
    pref = [0] * (n + 1)
    dp[0], pref[1] = 1, 1
    for i in range(1, n):
        # количество способов - сумма на отрезке [l, r]:
        if s[i] == '.':
            dp[i] = (pref[right[i] + 1] - pref[left[i]] + mod) % mod
        # обновляем префиксные суммы:
        pref[i + 1] = (pref[i] + dp[i]) % mod
    print(dp[-1])
tt = int(input())
while tt > 0:
    solve()
    tt -= 1