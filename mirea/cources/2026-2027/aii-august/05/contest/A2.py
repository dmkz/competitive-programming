# Время: 531 мс, Память: 86424 КБ
# функция находит список всех простых чисел <= NMAX:
def findPrimeNumbers(NMAX):
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
# читаем входные данные
q, L, R = map(int, input().split())
# находим простые до миллиона:
primes = findPrimeNumbers(1 << 20)
# вычёркиваем числа на отрезке [L, R], которые делятся на простые:
isPrime = [True] * (R - L + 1)
# вычеркнем 0 и 1:
if 0 >= L:
    isPrime[0 - L] = False
if 1 >= L:
    isPrime[1 - L] = False
# вычеркнем все остальные составные числа на отрезке [L, R]:
for p in primes:
    # очень важно начать вычёркивать с 2 * p, то есть случайно не вычеркнуть само p.
    # оптимально начать с p^2 и до конца с шагом p, но можно и с 2 * p:
    low = max(p, (L + p - 1) // p)
    high = R // p
    for i in range(low, high + 1):
        isPrime[i * p - L] = False
# строим префиксные суммы:
sums = [0]
for i in range(len(isPrime)):
    sums.append(sums[-1] + (L + i if isPrime[i] else 0))
# читаем запросы:
left = list(map(int, input().split()))
right = list(map(int, input().split()))
# отвечаем на них:
print(*[sums[right[i] + 1 - L] - sums[left[i] - L] for i in range(q)])