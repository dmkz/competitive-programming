from collections import defaultdict
mod = int(1e9) + 7
# Факториалы и обратные к ним:
NMAX = 1 << 21
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
    n, d, q = map(int, input().split())
    cnt = defaultdict(int)
    for i in range(n):
        a, c = map(int, input().split())
        cnt[a] += c
    while q > 0:
        ch = input().split()
        if ch[0] == '+':
            a, c = map(int, ch[1:])
            cnt[a] += c
        elif ch[0] == '-':
            a, c = map(int, ch[1:])
            cnt[a] -= c
            if cnt[a] == 0:
                del cnt[a]
        else:
            assert ch[0] == '?'
            k = int(ch[1])
            print(C(len(cnt) + k - 1, k))
        q -= 1
precalc() # вызов предподсчёта факториалов и обратных к ним
tt = int(input())
while tt > 0:
    solve()
    tt -= 1