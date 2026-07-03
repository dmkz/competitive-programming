# Сумма элементов массива в Python3

# Чтение массива
n = int(input())
a = list(map(int, input().split()))

# Подсчёт суммы вручную
manual_sum = 0
for x in a:
    manual_sum += x

# Подсчёт суммы через встроенную функцию
builtin_sum = sum(a)

# Вывод ответа
if manual_sum != builtin_sum:
    raise RuntimeError("Суммы не совпали")
print(builtin_sum)