# Пример: максимальная длина подотрезка положительных чисел с суммой не больше x.
# Решение: бинарный поиск по длине и проверка фиксированного окна.

def check(a, k, x):
    if k == 0:
        return True

    # Считаем сумму первого окна длины k.
    window_sum = sum(a[:k])
    if window_sum <= x:
        return True

    for left in range(len(a) - k):
        # Переходим к следующему окну той же длины.
        window_sum -= a[left]
        window_sum += a[left + k]
        if window_sum <= x:
            return True
    return False


n, x = map(int, input().split())
a = list(map(int, input().split()))

low = 0
high = n + 1
# На полуинтервале [low, high): low подходит, high ещё не подходит.
while high - low > 1:
    mid = (low + high) // 2
    if check(a, mid, x):
        low = mid
    else:
        high = mid

print(low)