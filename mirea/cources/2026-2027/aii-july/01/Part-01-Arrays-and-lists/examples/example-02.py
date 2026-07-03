# Чтение и вывод массива в исходном порядке в Python3

# Чтение размера массива и его элементов
n = int(input())
a = list(map(int, input().split()))

# Вывод элементов в исходном порядке
for x in a:
    print(x, end=' ')
print()