def check(a, x, k, mid):
    # Считаем цену подготовки mid наибольших чисел.
    need = 0
    for i in range(mid):
        need += max(0, x - a[i])
        if need > k: return False
    return True
# Читаем числа, запас увеличений и порог.
n, k, x = map(int, input().split())
a = list(map(int, input().split()))
# Сортируем по убыванию, чтобы улучшать первые элементы.
a.sort(reverse=True)
# Ищем наибольшее достижимое количество подготовленных чисел.
low, high = 0, n + 1
while high - low > 1:
    mid = (low + high) // 2
    if check(a, x, k, mid): low = mid
    else: high = mid
# Выводим максимальное количество.
print(low)