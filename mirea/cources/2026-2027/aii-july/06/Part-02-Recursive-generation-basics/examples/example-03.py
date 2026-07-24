# Пример: все перестановки чисел от 1 до n через used[].
# used[i] показывает, стоит ли число i + 1 уже в текущем префиксе.

n = int(input())
current = []
used = [False] * n


# Рекурсивно заполняем перестановку слева направо.
def dfs(pos: int) -> None:
	if pos == n:
		# Построили полную перестановку.
		print(*current)
		return

	# На позицию pos пробуем поставить любое свободное число.
	for value in range(1, n + 1):
		if used[value - 1]:
			continue

		# Добавляем свободное число в префикс.
		used[value - 1] = True
		current.append(value)
		dfs(pos + 1)

		# Откатываем состояние перед следующей веткой.
		current.pop()
		used[value - 1] = False


# Запускаем обход с пустого префикса.
dfs(0)