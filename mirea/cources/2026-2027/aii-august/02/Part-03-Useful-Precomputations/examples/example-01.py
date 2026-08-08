# Читаем массив:
n = int(input())
a = list(map(int, input().split()))
# Ищем первую позицию справа с отличающимся значением.
firstDifferent = [0] * n
firstDifferent[-1] = n
for i in range(n - 2, -1, -1):
    if a[i] == a[i + 1]:
        firstDifferent[i] = firstDifferent[i + 1]
    else:
        firstDifferent[i] = i + 1
# Выводим позиции в нумерации с единицы.
print(*(it + 1 for it in firstDifferent))