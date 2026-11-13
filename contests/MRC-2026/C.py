from bisect import bisect_left
from functools import cmp_to_key
NMAX = 100100
n = int(input())
a = list(map(int, input().split()))
a.reverse()
# сравнивать нужно a[i] * i! против a[j] * j!, причём a[i] и a[j] должны быть одного знака
pos, neg = [], []
for i in range(len(a)):
    if a[i] > 0: pos.append((a[i], i))
    else: neg.append((a[i], i))
# теперь будем сортировать в порядке возрастания
# a[i] * i! < a[j] * j!. Случаи:
# 1. Если i >= j, то a[i] * (i!/j!) < a[j]
# 2. Если i < j, то a[i] < a[j] * (j! / i!)
# отношение a[i] / a[j] может быть порядка 10^{18}, поэтому нужно предварительно подсчитать
# для каждого факториала с какими другими факториалами отношение не превысит 10^{18}
adj = [[] for _ in range(NMAX+1)]
inf = 2 * 10**18
for i in range(NMAX+1):
    # fact[j] / fact[i] = (i+1) * (i+2) * ... * j <= 10^{18}
    j = i
    prod = 1
    adj[i] = [(i, 1)]
    while prod * (j+1) < inf:
        j += 1
        prod *= j
        adj[i].append((j, prod))
# теперь можем начать сортировать:
def cmp(lhs, rhs):
    ai, i = lhs
    aj, j = rhs
    if i <= j:
        # a[i] < a[j] * (j!/i!)
        coeff = inf
        it = bisect_left(adj[i], (j, 0))
        if it != len(adj[i]): coeff = adj[i][it][1]
        x, y = a[i], a[j] * coeff
    else:
        # a[i] * (i! / j!) < a[j]
        coeff = inf
        it = bisect_left(adj[j], (i, 0))
        if it != len(adj[j]): coeff = adj[j][it][1]
        x, y = a[i] * coeff, a[j]
    return (x > y) - (x < y)
pos.sort(key=cmp_to_key(cmp))
neg.sort(key=cmp_to_key(cmp))
mod = 998244353
fact = [1] * (n+1)
for i in range(2, n+1):
    fact[i] = fact[i-1] * i % mod
# сначала минимум
if neg:
    aj, j = neg[0]
    se = (aj % mod * fact[j] % mod + mod) % mod
    print(se)
else:
    answ = inf
    for ai, _ in pos:
        answ = min(answ, ai)
    print(answ % mod)
# теперь максимум
if pos:
    ai, i = pos[-1]
    fi = (ai % mod * fact[i] % mod + mod) % mod
    print(fi)
else:
    answ = -inf
    for ai, _ in neg:
        answ = max(answ, ai)
    print((answ % mod + mod) % mod)