# Пример: пересечение двух массивов с учётом кратности.
# Ввод: n, m и два массива.
# Вывод: число общих элементов и сами общие элементы.

n, m = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))

a.sort()
b.sort()

common = []
i = 0
j = 0
# Сравниваем текущие элементы и двигаем тот указатель, где значение меньше.
while i < n and j < m:
    if a[i] == b[j]:
        common.append(a[i])
        i += 1
        j += 1
    elif a[i] < b[j]:
        i += 1
    else:
        j += 1

print(len(common))
print(*common)