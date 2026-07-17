# Пример: минимум на каждом суффиксе.
# Ввод: n и массив чисел.
# Вывод: массив минимумов на суффиксах.

n = int(input())
a = list(map(int, input().split()))

suf_min = [0] * n
suf_min[-1] = a[-1]
for i in range(n - 2, -1, -1):
    suf_min[i] = min(a[i], suf_min[i + 1])

print(*suf_min)