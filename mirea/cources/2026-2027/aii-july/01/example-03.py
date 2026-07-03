# Чтение массива через append и вывод в обратном порядке в Python3

# Чтение размера массива и подготовка списка
n = int(input())
numbers = list(map(int, input().split()))
a = []

# Чтение элементов и добавление их в конец списка
for x in numbers:
    a.append(x)

# Вывод элементов в обратном порядке
for i in range(n - 1, -1, -1):
    print(a[i], end=' ')
print()