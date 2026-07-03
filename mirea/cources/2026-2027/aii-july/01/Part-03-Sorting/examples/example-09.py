# Сортировка списка с key-функцией в Python3

# Чтение списка
n = int(input())
a = list(map(int, input().split()))

# В Python3 обычно задают key, а не собственный компаратор
a.sort(key=lambda x: (abs(x), x))

# Вывод результата
print(*a)