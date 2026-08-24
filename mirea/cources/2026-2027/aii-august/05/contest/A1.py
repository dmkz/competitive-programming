# Время: 171 мс, Память: 37688 КБ
# предподсчёт суммы всех простых решетом Эратосфена
NMAX = 1 << 20
primes = []
def precalc():
    # строим решето Эратосфена за O(n log(log(n))):
    global primes
    primes = [1] * (NMAX + 1)
    primes[0] = primes[1] = 0
    for i in range(2, int(NMAX ** 0.5) + 1):
        if primes[i]:
            for j in range(i * i, NMAX + 1, i):
                primes[j] = 0
    # считаем префиксные суммы прямо внутри решета:
    for i in range(2, NMAX + 1):
        primes[i] = (i if primes[i] else 0) + primes[i - 1]
def solve():
    # читаем запросы:
    q = int(input())
    r = list(map(int, input().split()))
    # отвечаем на них:
    print(*[primes[rr] for rr in r])
precalc() # вызываем предподсчёт один раз
tt = 1 # tt = int(input())
while tt > 0:
    solve()
    tt -= 1