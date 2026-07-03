# Нахождение минимума и максимума в Python3

# Чтение массива
n = int(input())
a = list(map(int, input().split()))

if not a:
    raise SystemExit

# Поиск минимума и максимума вручную
mn = a[0]
mx = a[0]
for i in range(1, n):
    if a[i] < mn:
        mn = a[i]
    if a[i] > mx:
        mx = a[i]

# Поиск минимума и максимума встроенными функциями
builtin_mn = min(a)
builtin_mx = max(a)

# Вывод ответа
if mn != builtin_mn or mx != builtin_mx:
    raise RuntimeError("Ответы не совпали")
print(mn, mx)