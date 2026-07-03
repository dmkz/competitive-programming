# Первый элемент, не меньший x, в Python3

# Чтение отсортированного массива и значения x
n = int(input())
a = list(map(int, input().split()))
x = int(input())

# Ищем минимальный индекс, на котором a[index] >= x
left = 0
right = n
while left < right:
    mid = (left + right) // 2
    if a[mid] < x:
        left = mid + 1
    else:
        right = mid

# Выводим позицию и значение найденного элемента или -1
if left == n:
    print(-1)
else:
    print(left, a[left])