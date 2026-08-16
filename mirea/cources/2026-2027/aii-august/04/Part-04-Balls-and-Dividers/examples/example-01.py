mod = 10 ** 9 + 7
def power(a, exponent):
	answ = 1
	while exponent > 0:
		if exponent % 2 == 1: answ = answ * a % mod
		a = a * a % mod
		exponent //= 2
	return answ
n, k = map(int, input().split())
# Предподсчитываем факториалы для сочетания C(n - 1, k - 1).
fact = [1] * (n + 1)
for i in range(1, n + 1): fact[i] = fact[i - 1] * i % mod
invFact = [1] * (n + 1)
invFact[n] = power(fact[n], mod - 2)
for i in range(n, 0, -1): invFact[i - 1] = invFact[i] * i % mod
# Выбираем k - 1 промежутков между n единицами для знаков сложения.
print(fact[n - 1] * invFact[k - 1] % mod * invFact[n - k] % mod)