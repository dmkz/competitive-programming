# Пример: существует ли пара элементов с суммой x.
# Ввод: n, x и массив a.
# Вывод: YES, если такая пара существует, иначе NO.

n, x = map(int, input().split())
a = list(map(int, input().split()))

a.sort()

left = 0
right = n - 1
ok = False

while left < right:
    current_sum = a[left] + a[right]
    if current_sum == x:
        ok = True
        break
    if current_sum < x:
        # Левый элемент слишком мал, увеличиваем сумму.
        left += 1
    else:
        # Правый элемент слишком велик, уменьшаем сумму.
        right -= 1

print('YES' if ok else 'NO')