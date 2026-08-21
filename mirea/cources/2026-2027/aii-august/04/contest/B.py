mod = int(1e9) + 7
# Факториалы и обратные к ним:
NMAX = 1 << 20
fact, ifact = [0] * NMAX, [0] * NMAX
def precalc():
    fact[0] = 1
    for i in range(1, NMAX):
        fact[i] = fact[i - 1] * i % mod
    ifact[NMAX - 1] = pow(fact[NMAX - 1], mod - 2, mod)
    for i in range(NMAX - 2, -1, -1):
        ifact[i] = (i + 1) * ifact[i + 1] % mod
# Биномиальный коэффициент:
def C(n, k):
    if n < 0 or k < 0 or k > n:
        return 0
    return fact[n] * ifact[k] % mod * ifact[n - k] % mod
# Решение:
def solve():
    n, q = map(int, input().split())
    r, c = list(map(int, input().split())), list(map(int, input().split()))
    for i in range(1, q + 1):
        print((C(n * n - i, n - i) - fact[n - i] + mod) % mod, end=' ')
    print()
precalc() # вызов предподсчёта факториалов и обратных к ним
tt = int(input())
while tt > 0:
    solve()
    tt -= 1