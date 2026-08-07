# Читаем уже отсортированный массив и число, для которого ищем границу.
n = int(input())
a = list(map(int, input().split()))
x = int(input())
# low точно не подходит, high точно подходит как служебная позиция n.
low, high = -1, n
while high - low > 1:
    mid = (low + high) // 2
    if a[mid] >= x: high = mid
    else: low = mid
print(high)