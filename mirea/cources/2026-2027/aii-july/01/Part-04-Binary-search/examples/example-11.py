# Ручной бинарный поиск элемента в Python3

# Чтение отсортированного массива и значения x
n = int(input())
a = list(map(int, input().split()))
x = int(input())

# Поддерживаем текущий отрезок поиска и каждый раз отбрасываем половину
left = 0
right = n - 1
answer = -1

while left <= right:
    mid = (left + right) // 2
    if a[mid] == x:
        answer = mid
        break
    if a[mid] < x:
        left = mid + 1
    else:
        right = mid - 1

# Выводим индекс найденного элемента или -1
print(answer)