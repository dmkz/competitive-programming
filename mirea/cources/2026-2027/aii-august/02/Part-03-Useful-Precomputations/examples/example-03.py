# Читаем массив:
n = int(input())
a = list(map(int, input().split()))
# Считаем длину строго возрастающего подотрезка из каждой позиции.
incLen = [0] * n
incLen[-1] = 1
for i in range(n - 2, -1, -1):
    if a[i] < a[i + 1]: incLen[i] = incLen[i + 1] + 1
    else: incLen[i] = 1
# Выводим длины возрастающих подотрезков.
print(*incLen)