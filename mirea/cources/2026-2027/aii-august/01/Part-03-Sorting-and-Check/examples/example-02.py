def check(a, b, k, mid):
    # Считаем цену mid запланированных побед.
    need = 0
    first_win = len(a) - mid
    for i in range(mid):
        need += max(0, b[i] - a[first_win + i])
        if need > k: return False
    return True
# Читаем оба мультимножества и запас увеличений.
n, k = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
# Сортируем, чтобы сопоставлять малые и большие значения по ролям.
a.sort()
b.sort()
# Ищем наибольшее достижимое количество побед.
low, high = 0, n + 1
while high - low > 1:
    mid = (low + high) // 2
    if check(a, b, k, mid): low = mid
    else: high = mid
# Выводим максимальное количество побед.
print(low)