# Максимальный элемент, меньший x, в Python3

from bisect import bisect_left

# Чтение отсортированного массива и значения x
n = int(input())
a = list(map(int, input().split()))
x = int(input())

# Ручной бинарный поиск последнего индекса, на котором a[index] < x
left = -1
right = n
while right - left > 1:
    mid = (left + right) // 2
    if a[mid] < x:
        left = mid
    else:
        right = mid

# Через bisect_left достаточно взять предыдущий элемент
pos = bisect_left(a, x)
has_manual = left != -1
has_library = pos != 0

if has_manual != has_library:
    raise RuntimeError("Ответы не совпали")
if has_manual and a[left] != a[pos - 1]:
    raise RuntimeError("Ответы не совпали")

# Выводим ответ двумя способами
if not has_manual:
    print("NO")
    print("NO")
else:
    print(a[left])
    print(a[pos - 1])