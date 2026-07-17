# Пример: прибавление арифметической прогрессии на отрезке.
# Ввод: n, q и q запросов вида l r d.
# Вывод: итоговый массив после всех прибавлений.

n, q = map(int, input().split())

# diff хранит второй разностный слой.
diff = [0] * (n + 3)
for _ in range(q):
    l, r, d = map(int, input().split())
    length = r - l + 1
    diff[l] += d
    diff[r + 1] -= (length + 1) * d
    diff[r + 2] += length * d

# Первый префиксный проход восстанавливает наклон.
a = [0] * (n + 1)
current = 0
for i in range(1, n + 1):
    current += diff[i]
    a[i] = current

# Второй префиксный проход превращает наклон в итоговый массив.
s = [0] * (n + 1)
for i in range(1, n + 1):
    s[i] = s[i - 1] + a[i]

print(*s[1:])