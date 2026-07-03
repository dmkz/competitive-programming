# Стандартные приёмы бинарного поиска в Python3

from bisect import bisect_left, bisect_right

# Чтение отсортированного массива и значения x
n = int(input())
a = list(map(int, input().split()))
x = int(input())

# В Python3 функции bisect_left и bisect_right играют роль lower_bound и upper_bound
left = bisect_left(a, x)
right = bisect_right(a, x)
found = left < len(a) and a[left] == x

# Диапазон [left, right) является аналогом equal_range,
# а по его границам легко посчитать количества элементов
equal_left = left
equal_right = right
equal_count = right - left
less = left
equal = equal_count
greater = len(a) - right

# Выводим позиции, факт наличия элемента и количества элементов по отношению к x
print(left, right)
print("YES" if found else "NO")
print(equal_left, equal_right, equal_count)
print(less, equal, greater)