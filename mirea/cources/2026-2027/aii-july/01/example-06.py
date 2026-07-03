# Нахождение максимума, его количества и позиций в Python3

# Чтение массива
n = int(input())
a = list(map(int, input().split()))

if not a:
    raise SystemExit

# Поиск ответа с помощью нескольких проходов
mx_multi = max(a)
cnt_multi = a.count(mx_multi)
first_multi = a.index(mx_multi)
last_multi = len(a) - 1 - a[::-1].index(mx_multi)

# Поиск ответа за один проход
mx = a[0]
cnt = 1
first = 0
last = 0

for i in range(1, n):
    if a[i] > mx:
        mx = a[i]
        cnt = 1
        first = i
        last = i
    elif a[i] == mx:
        cnt += 1
        last = i

# Вывод ответа
if (mx, cnt, first, last) != (mx_multi, cnt_multi, first_multi, last_multi):
    raise RuntimeError("Ответы не совпали")
print(mx, cnt, first, last)