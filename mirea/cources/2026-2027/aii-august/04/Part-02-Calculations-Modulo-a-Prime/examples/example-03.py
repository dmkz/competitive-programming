mod = 10 ** 9 + 7
n, k = map(int, input().split())
limit = min(k, n - k)
# Последовательно домножаем числитель и делим на очередной знаменатель.
answ = 1
for i in range(1, limit + 1):
	answ = answ * (n - i + 1) % mod
	answ = answ * pow(i, -1, mod) % mod
print(answ)