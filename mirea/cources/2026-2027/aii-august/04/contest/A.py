mod = int(1e9) + 7
# Факториалы и обратные к ним:
NMAX = 200200
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
    n = int(input())
    nOdd, nEven = 0, 0
    for ai in map(int, input().split()):
        if ai % 2 == 1:
            nOdd += 1
        else:
            nEven += 1
    answ = 0
    for k in range(min(nOdd, nEven) + 1):
        answ = (answ + C(nOdd, k) * C(nEven, k)) % mod
    print(answ)
precalc() # вызов предподсчёта факториалов и обратных к ним
tt = int(input())
while tt > 0:
    solve()
    tt -= 1