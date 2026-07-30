# Будем поддерживать множество элементов в порядке возрастания, но хранить отдельно его
# левую и правую половины. Тогда медиана будет стоять в конце левой половины. Перед вставкой
# нового элемента мы сначала определяем, в какую половину он попадает, вставляем в неё, а
# затем мы делаем размеры половин примерно равными, перекидывая из начала правой половины в
# конец левой, или из конца левой половины в начало правой.
import heapq


def solve():
    left = []
    right = []

    def insertAndRebalance(x):
        # функция вставляет элемент и приводит баланс между размерами половин в порядок
        # половины уже отсортированы. Нужно определить, куда попадает x, и вставить его:
        if left and x <= -left[0]:
            heapq.heappush(left, -x)
        else:
            heapq.heappush(right, x)
        # перекидываем из левой половины в правую:
        while len(left) > len(right) + 1:
            heapq.heappush(right, -heapq.heappop(left))
        # перекидываем из правой половины в левую:
        while len(right) > len(left):
            heapq.heappush(left, -heapq.heappop(right))

    # читаем данные и вставляем их в множество:
    n, q = map(int, input().split())
    for x in map(int, input().split()):
        insertAndRebalance(x)
    # обрабатываем запросы:
    for x in map(int, input().split()):
        insertAndRebalance(x)
        print(-left[0], end=' ')
    print()


tt = int(input())
while tt > 0:
    solve()
    tt -= 1
