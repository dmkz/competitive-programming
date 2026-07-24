# Пример: все правильные скобочные последовательности из n пар скобок.
# Здесь допустимый префикс — тот, у которого число ')' не превосходит число '('.

n = int(input())
current = []


# Строим только те префиксы, которые ещё можно продолжить до правильной скобочной последовательности.
def dfs(open_used: int, close_used: int) -> None:
	if open_used == n and close_used == n:
		# Построили полную правильную последовательность.
		print(''.join(current))
		return

	if open_used < n:
		# Открывающую скобку можно добавить, пока не использовали все n штук.
		current.append('(')
		dfs(open_used + 1, close_used)
		current.pop()

	if close_used < open_used:
		# Закрывающую скобку добавляем только к допустимому префиксу.
		current.append(')')
		dfs(open_used, close_used + 1)
		current.pop()


# Запускаем перебор из пустого префикса.
dfs(0, 0)