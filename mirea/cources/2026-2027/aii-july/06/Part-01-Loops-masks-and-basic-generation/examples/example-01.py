# Пример: все перестановки чисел от 1 до n.

from itertools import permutations


# Считываем размер перестановки.
n = int(input())

# permutations сам перебирает все перестановки по порядку.
for p in permutations(range(1, n + 1)):
	print(*p)