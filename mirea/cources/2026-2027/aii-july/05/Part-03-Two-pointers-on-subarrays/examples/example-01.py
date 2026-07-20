# Пример: максимальная длина подотрезка положительных чисел с суммой не больше x.
# Решение: прямой проход двумя указателями.

n, x = map(int, input().split())
a = list(map(int, input().split()))

left = 0
window_sum = 0
answer = 0

for right in range(n):
    # Расширяем окно вправо.
    window_sum += a[right]
    # Пока окно плохое, сдвигаем левую границу.
    while window_sum > x:
        window_sum -= a[left]
        left += 1
    answer = max(answer, right - left + 1)

print(answer)