# Пример: число перестановок чисел от 1 до n, в которых число i не стоит на позиции i.
# Откат обязателен: после каждой ветки снимаем used[] и убираем последнее число из префикса.

n = int(input())
ways = 0
current = []
used = [False] * n


# Строим перестановку слева направо и откатываем состояние после каждой ветки.
def dfs(pos: int) -> None:
	global ways
	if pos == n:
		# Нашли одну полную подходящую перестановку.
		ways += 1
		return

	for value in range(1, n + 1):
		if used[value - 1]:
			continue

		# Не разрешаем числу value стоять на его собственной позиции.
		if value == pos + 1:
			continue

		# Занимаем число value и углубляемся.
		used[value - 1] = True
		current.append(value)
		dfs(pos + 1)

		# Откатываем все изменения перед следующей веткой.
		current.pop()
		used[value - 1] = False


# Запускаем поиск с пустого префикса.
dfs(0)
print(ways)