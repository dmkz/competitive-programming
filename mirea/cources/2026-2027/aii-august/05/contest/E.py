# Время: 375 мс, Память: 10316 КБ
# модульная арифметика:
mod = 998244353
def sub(a, b):
    return (a - b) % mod
def add(a, b):
    return (a + b) % mod
def mul(a, b):
    return a * b % mod
# сумма геометрической прогрессии:
def geom(a, n):
    # 1 + a + ... + a^n = (a^{n+1} - 1) / (a - 1)
    if n == 0:
        return 1
    p = sub(pow(a, n + 1, mod), 1)
    q = pow(sub(a, 1), -1, mod)
    return mul(p, q)
# функция находит список всех простых чисел <= NMAX:
def findPrimeNumbers(NMAX):
    if (NMAX < 2): NMAX = 2; # передан слишком маленький NMAX
    # строим решето Эратосфена за O(n log(log(n))):
    isPrime = [True] * (NMAX + 1)
    isPrime[0] = isPrime[1] = False
    for i in range(2, int(NMAX ** 0.5) + 1):
        if isPrime[i]:
            for j in range(i * i, NMAX + 1, i):
                isPrime[j] = False
    # возвращаем результат:
    primes = []
    for i in range(2, NMAX + 1):
        if isPrime[i]:
            primes.append(i)
    return primes
# формула Лежандра считает, сколько раз n! делится на простое p
def Legendre(n, p):
    result = 0
    while n > 0:
        n //= p
        result += n
    return result
# решение задачи:
def solve():
    # читаем входные данные
    n, m, k, r = map(int, input().split())
    # находим простые числа до max(n, m):
    primes = findPrimeNumbers(max(n, m))
    # раскладываем каждый из факториалов на простые множители по формуле Лежандра
    answ = 1
    for p in primes:
        # считаем степень вхождения p в число C(n,k) = n!/k!/(n-k)!:
        countInN = Legendre(n, p)
        countInN -= Legendre(k, p)
        countInN -= Legendre(n - k, p)
        # считаем степень вхождения p в число C(m,r) = m!/r!/(m-r)!:
        countInM = Legendre(m, p)
        countInM -= Legendre(r, p)
        countInM -= Legendre(m - r, p)
        # обновляем сумму делителей:
        answ = mul(answ, geom(p, min(countInN, countInM)))
    print(answ)
tt = int(input())
while tt > 0:
    solve()
    tt -= 1