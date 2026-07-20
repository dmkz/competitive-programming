# Пример: минимум в каждом окне длины k через монотонную двустороннюю очередь.
# Ввод: n, k и массив a.
# Вывод: минимумы всех окон длины k слева направо.

from collections import deque


n, k = map(int, input().split())
a = list(map(int, input().split()))

dq = deque()
answer = []

for i in range(n):
    # Выкидываем из конца все элементы не лучше текущего.
    while dq and a[dq[-1]] >= a[i]:
        dq.pop()
    dq.append(i)

    left = i - k + 1
    if left < 0:
        continue

    # Убираем из начала индексы, которые уже вышли из окна.
    while dq and dq[0] < left:
        dq.popleft()
    answer.append(a[dq[0]])

print(*answer)