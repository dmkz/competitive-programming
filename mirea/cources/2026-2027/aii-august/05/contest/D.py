# Решение корректное, но получает TLE: работает за 5437 мс
# предподсчёт всех простых чисел до корня из 10^9:
NMAX = int((10 ** 9 + 100) ** 0.5)
primes = []
def precalc():
    # для разнообразия найдём все простые числа без решета Эратосфена: при проверке
    # очередного числа проверяем, делится ли оно на уже найденные. Если не делится — простое
    global primes
    primes = [2, 3, 5, 7]
    for x in range(8, NMAX + 1):
        isPrime = True
        for p in primes:
            if p * p > x:
                break
            if x % p == 0:
                isPrime = False
                break
        if isPrime:
            primes.append(x)
# функция для факторизации заданного числа: находит список простых делителей числа
def factor(x):
    result = [] # пары (простое, его степень)
    for p in primes:
        if p * p > x:
            break # факторизуем до корня, после корня делаем break
        if x % p == 0:
            result.append([p, 0])
            # делим, пока делится:
            while x % p == 0:
                x //= p
                result[-1][1] += 1
    # могло остаться простое больше корня:
    if x > 1:
        result.append([x, 1])
    return result
# функция для восстановления всех делителей, зная факторизацию:
def divisors(primeDivisors):
    curr = [1]
    for p, k in primeDivisors:
        # у нас k+1 вариантов: взять p^i в делитель, 0 <= i <= k
        prevSize = len(curr)
        # полуинтервал [0, prevSize) содержит все делители до рассмотрения p^k
        # мы должны умножить на p^i каждый из них, где 0 <= i <= k
        mult = 1
        for i in range(1, k + 1):
            mult *= p
            for j in range(prevSize):
                curr.append(curr[j] * mult)
    return curr
def solve():
    # читаем данные:
    n = int(input())
    a = list(map(int, input().split()))
    # факторизуем каждое число и для каждого делителя считаем, сколько чисел оно делит:
    cnt = {} # обычный словарь даёт TLE
    for ai in a:
        for d in divisors(factor(ai)):
            cnt[d] = cnt.get(d, 0) + 1
    # находим максимальное число, которое делит два элемента массива:
    answ = 1
    for d, k in cnt.items():
        if k > 1:
            answ = max(answ, d)
    print(answ)
precalc() # предподсчитываем все простые числа один раз
tt = int(input())
while tt > 0:
    solve()
    tt -= 1