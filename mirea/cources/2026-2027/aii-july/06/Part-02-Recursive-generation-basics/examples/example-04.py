# Пример: все подмножества множества {1, ..., n}.
# На каждом шаге рекурсия решает, брать текущий элемент или нет.

n = int(input())
current = []


# Печатаем одно готовое подмножество в виде {1, 3, 5}.
def print_subset() -> None:
	print('{' + ', '.join(map(str, current)) + '}')


# Для каждого value решаем: брать его в подмножество или нет.
def dfs(value: int) -> None:
	if value > n:
		# Построили одно полное подмножество.
		print_subset()
		return

	# Ветка 1: не берём value.
	dfs(value + 1)

	# Ветка 2: берём value.
	current.append(value)
	dfs(value + 1)
	current.pop()


# Запускаем перебор с первого числа.
dfs(1)