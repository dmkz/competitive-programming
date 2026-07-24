# Пример: максимальная сумма подмножества, не превосходящая limit_sum.
# Решаем ту же задачу через meet-in-the-middle.

from bisect import bisect_right


# Строим все суммы подмножеств для одной половины массива.
def build_sums(part: list[int]) -> list[int]:
	sums = []
	for mask in range(1 << len(part)):
		current_sum = 0
		for i in range(len(part)):
			if (mask >> i) & 1:
				current_sum += part[i]
		sums.append(current_sum)
	return sums


n, limit_sum = map(int, input().split())
a = list(map(int, input().split()))

# Делим массив на две половины, чтобы перебирать их независимо.
mid = n // 2
left = a[:mid]
right = a[mid:]

# Генерируем все суммы отдельно для каждой половины.
left_sums = build_sums(left)
right_sums = sorted(build_sums(right))

best = 0
for left_sum in left_sums:
	if left_sum > limit_sum:
		continue

	# Ищем максимальную допустимую сумму правой половины.
	need = limit_sum - left_sum
	pos = bisect_right(right_sums, need) - 1
	if pos >= 0:
		best = max(best, left_sum + right_sums[pos])
	else:
		best = max(best, left_sum)

# Печатаем лучшую допустимую сумму.
print(best)