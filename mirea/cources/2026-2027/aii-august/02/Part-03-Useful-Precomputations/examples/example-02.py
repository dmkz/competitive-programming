# Читаем массив:
n = int(input())
a = list(map(int, input().split()))
# Считаем длину блока одинаковых значений, начинающегося в каждой позиции.
blockLen = [0] * n
blockLen[-1] = 1
for i in range(n - 2, -1, -1):
    if a[i] == a[i + 1]: blockLen[i] = blockLen[i + 1] + 1
    else: blockLen[i] = 1
# Выводим длины блоков.
print(*blockLen)