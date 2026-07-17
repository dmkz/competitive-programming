# Пример: функция Эйлера от произведения чисел на отрезке.
# Ввод: n, q, массив чисел от 1 до 300 и q запросов [l, r] в единичной индексации.
# Вывод: phi(product(a[l..r])) по модулю 10^9 + 7 для каждого запроса.

LIMIT = 300
MOD = 10**9 + 7


def build_primes():
    is_prime = [True] * (LIMIT + 1)
    is_prime[0] = False
    is_prime[1] = False
    primes = []

    for value in range(2, LIMIT + 1):
        if not is_prime[value]:
            continue
        primes.append(value)
        for multiple in range(value * 2, LIMIT + 1, value):
            is_prime[multiple] = False

    return primes


n, q = map(int, input().split())
a = list(map(int, input().split()))

primes = build_primes()
primes_count = len(primes)

# factors[value][j] хранит степень j-го простого в разложении value.
factors = [[0] * primes_count for _ in range(LIMIT + 1)]
for value in range(1, LIMIT + 1):
    current = value
    for j, prime in enumerate(primes):
        while current % prime == 0:
            factors[value][j] += 1
            current //= prime
        if current == 1:
            break

# pref[i][j] хранит суммарную степень j-го простого среди первых i чисел.
pref = [[0] * primes_count for _ in range(n + 1)]
for i in range(n):
    pref[i + 1] = pref[i][:]
    for j in range(primes_count):
        pref[i + 1][j] += factors[a[i]][j]

for _ in range(q):
    l, r = map(int, input().split())
    l -= 1
    r -= 1

    answer = 1
    for j, prime in enumerate(primes):
        exponent = pref[r + 1][j] - pref[l][j]
        if exponent == 0:
            continue

        # phi(p^k) = p^k - p^(k-1), затем берём произведение по модулю.
        full_power = pow(prime, exponent, MOD)
        smaller_power = pow(prime, exponent - 1, MOD)
        term = (full_power - smaller_power) % MOD
        answer = (answer * term) % MOD

    print(answer)