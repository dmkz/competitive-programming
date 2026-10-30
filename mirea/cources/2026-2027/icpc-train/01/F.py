from array import array
# арифметика по простому модулю:
mod, NMAX = 10**9+7, 2020
def add(x, y):
    x += y
    return x-mod if x >= mod else x
def mul(a, b, c=None):
    if c is None: return a*b%mod
    return mul(c, mul(a, b))
fact = [1]*NMAX
for i in range(1, NMAX): fact[i] = mul(fact[i-1], i)
ifact = [pow(fact[NMAX-1], -1, mod)]*NMAX
for i in range(NMAX-2, -1, -1):
    ifact[i] = mul(ifact[i+1], i+1)
def C(n, k):
    if k < 0 or k > n or n < 0: return 0
    return mul(fact[n], ifact[k], ifact[n-k])
# решение задачи:
def solve():
    n, k, d = map(int, input().split())
    if d >= n:
        print(C(n, k))
        return
    # поделим фонари на группы с одинаковым остатком при делении на d: такие группы независимы
    # в одной группе не должно быть двух подряд взятых фонарей
    # посчитаем количество способов взять t фонарей в каждой группе
    dp = [array('i', [0])*(2*(k+1)) for _ in range(n+1)]
    dp[0][0] = 1
    for i in range(1, len(dp)):
        # не берём i-й фонарь:
        for t in range(k+1):
            dp[i][2*t] = add(dp[i][2*t], dp[i-1][2*t])
            dp[i][2*t] = add(dp[i][2*t], dp[i-1][2*t+1])
        # берём i-й фонарь: не берём предыдущий
        for t in range(k):
            dp[i][2*t+3] = add(dp[i][2*t+3], dp[i-1][2*t])
    # теперь нам нужно перемножить группы: скомбинировать их друг с другом
    # combined[d][k] = кол-во способов среди первых d групп выбрать k фонарей
    combined = [array('i', [0])*(k+1) for _ in range(d+1)]
    combined[0][0] = 1
    for i in range(d):
        gsize = n//d+(i < n%d)
        for take in range(min(k, gsize)+1):
            ways = (dp[gsize][2*take]+dp[gsize][2*take+1])%mod
            for prev in range(k-take+1):
                combined[i+1][prev+take] = add(combined[i+1][prev+take], mul(combined[i][prev], ways))
    print(combined[d][k])
tt = int(input())
for _ in range(tt): solve()