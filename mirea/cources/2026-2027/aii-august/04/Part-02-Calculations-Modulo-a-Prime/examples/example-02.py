mod = 10 ** 9 + 7
def power(a, exponent):
	answ = 1
	while exponent > 0:
		if exponent % 2 == 1: answ = answ * a % mod
		a = a * a % mod
		exponent //= 2
	return answ
maxN, q = map(int, input().split())
# Предподсчитываем факториалы до наибольшей границы запросов.
fact = [1] * (maxN + 1)
for i in range(1, maxN + 1):
	fact[i] = fact[i - 1] * i % mod
# Один обратный факториал восстанавливает все остальные движением вниз.
invFact = [1] * (maxN + 1)
invFact[maxN] = power(fact[maxN], mod - 2)
for i in range(maxN, 0, -1):
	invFact[i - 1] = invFact[i] * i % mod
# Для каждого запроса подставляем три предподсчитанных значения в формулу.
for queryId in range(q):
	n, k = map(int, input().split())
	if k < 0 or k > n: print(0)
	else: print(fact[n] * invFact[k] % mod * invFact[n - k] % mod)