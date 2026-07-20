# Пример: сумма в каждом окне длины k.
# Ввод: n, k и массив a.
# Вывод: суммы всех окон длины k слева направо.

n, k = map(int, input().split())
a = list(map(int, input().split()))

# Сначала считаем сумму первого окна.
window_sum = sum(a[:k])
answer = []

for left in range(n - k + 1):
    answer.append(window_sum)
    if left + k < n:
        # Убираем ушедший слева элемент и добавляем новый справа.
        window_sum -= a[left]
        window_sum += a[left + k]

print(*answer)