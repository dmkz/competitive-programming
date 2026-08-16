mod = 10 ** 9 + 7
def power(a, exponent):
	answ = 1
	while exponent > 0:
		if exponent % 2 == 1:
			answ = answ * a % mod
		a = a * a % mod
		exponent //= 2
	return answ
n, m, r, c = map(int, input().split())
maxN = n + m
# Предподсчитываем факториалы, чтобы быстро получать сочетания.
fact = [1] * (maxN + 1)
for i in range(1, maxN + 1):
	fact[i] = fact[i - 1] * i % mod
invFact = [1] * (maxN + 1)
invFact[maxN] = power(fact[maxN], mod - 2)
for i in range(maxN, 0, -1):
	invFact[i - 1] = invFact[i] * i % mod
def combination(allCount, chosen):
	if chosen < 0 or chosen > allCount:
		return 0
	answ = fact[allCount]
	answ = answ * invFact[chosen] % mod
	answ *= invFact[allCount - chosen]
	return answ % mod
# Вычитаем пути через закрытую клетку из всех маршрутов.
allWays = combination(n + m - 2, n - 1)
throughCell = combination(r + c - 2, r - 1)
throughCell *= combination(n + m - r - c, n - r)
print((allWays - throughCell) % mod)