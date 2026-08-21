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
# Количество путей из (r1, c1) в (r2, c2):
def cntWays(r1, c1, r2, c2):
    assert r1 <= r2
    if c1 > c2:
        return 0
    dr, dc = r2 - r1, c2 - c1
    return C(dr + dc, dr)
# Решение:
def solve():
    n, m, r1, c1, r2, c2 = map(int, input().split())
    # отсортируем клетки так, чтобы (r1, c1) шла раньше (r2, c2)
    if r1 > r2 or (r1 == r2 and c1 > c2):
        r1, r2 = r2, r1
        c1, c2 = c2, c1
    # считаем пути по формуле включений-исключений:
    answ = cntWays(1, 1, n, m)
    answ -= cntWays(1, 1, r1, c1) * cntWays(r1, c1, n, m)
    answ -= cntWays(1, 1, r2, c2) * cntWays(r2, c2, n, m)
    answ += cntWays(1, 1, r1, c1) * cntWays(r1, c1, r2, c2) % mod * cntWays(r2, c2, n, m)
    # выводим ответ:
    print((answ % mod + mod) % mod)
precalc() # вызов предподсчёта факториалов и обратных к ним
tt = int(input())
while tt > 0:
    solve()
    tt -= 1