# Пример: слияние двух отсортированных массивов в один.
# Ввод: n, m и два массива a и b, уже отсортированные по неубыванию.
# Вывод: объединённый отсортированный массив.

n, m = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))

merged = []

i = 0
j = 0
while i < n and j < m:
    if a[i] <= b[j]:
        # Берём меньший текущий элемент из первого массива.
        merged.append(a[i])
        i += 1
    else:
        # Берём меньший текущий элемент из второго массива.
        merged.append(b[j])
        j += 1

while i < n:
    merged.append(a[i])
    i += 1
while j < m:
    merged.append(b[j])
    j += 1

print(*merged)