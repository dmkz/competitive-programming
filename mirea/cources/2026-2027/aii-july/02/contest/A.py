# Моделируем запросы к очереди. Используем структуру данных deque.
from collections import deque

def solve():
    nQ = int(input())
    q = deque()
    for _ in range(nQ):
        query = input().split()
        c = query[0]
        if c == '+':
            # добавление элемента в конец очереди:
            x = int(query[1])
            q.append(x)
        else:
            # вывод первого элемента в очереди и его удаление:
            print(q.popleft())

tt = int(input())
for _ in range(tt):
    solve()