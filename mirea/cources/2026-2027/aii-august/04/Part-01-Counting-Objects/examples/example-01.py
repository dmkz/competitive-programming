n, k = map(int, input().split())
# Считаем произведение всех чисел от 1 до n.
permutation = 1
for i in range(1, n + 1):
	permutation *= i
# В размещении выбираем только первые k множителей.
arrangement = 1
for i in range(k):
	arrangement *= n - i
# После каждого шага частное остаётся целым и равно очередному сочетанию.
combination = 1
for i in range(1, k + 1):
	combination *= n - i + 1
	combination //= i
print(permutation)
print(arrangement)
print(combination)