# Пример: максимальная сумма подмножества, не превосходящая limit_sum.
# Для малого n просто перебираем все маски.

n, limit_sum = map(int, input().split())
a = list(map(int, input().split()))

# Перебираем все подмножества битовой маской.
best = 0
for mask in range(1 << n):
	current_sum = 0
	for i in range(n):
		# Бит i показывает, берём ли элемент a[i].
		if (mask >> i) & 1:
			current_sum += a[i]
	if current_sum <= limit_sum:
		best = max(best, current_sum)

# Печатаем лучшую допустимую сумму.
print(best)