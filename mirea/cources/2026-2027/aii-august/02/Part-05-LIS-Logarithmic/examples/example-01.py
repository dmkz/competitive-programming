from bisect import bisect_left
# Читаем последовательность:
n = int(input())
a = list(map(int, input().split()))
# Инициализируем пустую подпоследовательность и недостижимые длины:
inf = 10 ** 30
dp = [-inf] + [inf] * n
answ = 0
# Обрабатываем каждое число бинарным поиском:
for i in range(n):
    pos = bisect_left(dp, a[i], 1)
    dp[pos] = a[i]
    answ = max(answ, pos)
# Выводим длину лучшей подпоследовательности:
print(answ)