# модульная арифметика:
mod = 998244353
def mul(a, b):
    return a * b % mod
def add(a, b):
    return (a + b) % mod
def sub(a, b):
    return (a - b + mod) % mod
def inv(a):
    return pow(a, -1, mod)
# факториалы и обратные к ним:
NMAX = 2 * 1024 * 1024
fact = [1] * (NMAX+1)
for i in range(2, NMAX+1):
    fact[i] = mul(fact[i-1], i)
ifact = [1] * (NMAX+1)
ifact[NMAX] = inv(fact[NMAX])
for i in range(NMAX-1, -1, -1):
    ifact[i] = mul(ifact[i+1], i+1)
# биномиальный коэффициент:
def C(n, k):
    if n < 0 or k < 0 or k > n: return 0
    return mul(fact[n], mul(ifact[k], ifact[n-k]))
# количество путей (r1, c1) -> (r2, c2):
def cntWays(r1, c1, r2, c2):
    dr, dc = r2 - r1, c2 - c1
    if dr < 0 or dc < 0: return 0
    return C(dr+dc, dr)
# решение задачи:
def solve():
    # читаем данные:
    n, m, q = map(int, input().split())
    # сколько всего путей из (1, 1) в (n, m):
    total = cntWays(1, 1, n, m)
    for _ in range(q):
        # читаем текущий набор ловушек:
        k = int(input())
        r = list(map(int, input().split()))
        c = list(map(int, input().split()))
        # считаем ответ: "безопасные пути" = "все пути" вычесть "пути через ловушки"
        answ = total
        for i in range(k):
            answ = sub(answ, mul(cntWays(1, 1, r[i], c[i]), cntWays(r[i], c[i], n, m)))
        print(answ)
tt = 1
for _ in range(tt):
    solve()