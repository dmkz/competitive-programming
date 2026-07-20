# Пример: минимум в каждом окне длины k через двоичную кучу и ленивое удаление.
# Ввод: n, k и массив a.
# Вывод: минимумы всех окон длины k слева направо.

import heapq
from collections import defaultdict


n, k = map(int, input().split())
a = list(map(int, input().split()))

heap = []
deleted = defaultdict(int)
# Кладём в кучу первое окно.
for i in range(k):
    heapq.heappush(heap, a[i])

answer = []
for left in range(n - k + 1):
    # Убираем с вершины элементы, которые уже помечены как удалённые.
    while heap and deleted[heap[0]] > 0:
        value = heap[0]
        deleted[value] -= 1
        if deleted[value] == 0:
            del deleted[value]
        heapq.heappop(heap)

    answer.append(heap[0])

    if left + k < n:
        # Левый элемент покидает окно, а новый справа в него входит.
        deleted[a[left]] += 1
        heapq.heappush(heap, a[left + k])

print(*answer)