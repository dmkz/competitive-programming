from bisect import bisect_left

def solve():
    # читаем запросы и запоминаем использованные координаты:
    q = int(input())
    queries = list(map(int, input().split()))
    x = [-1000000000, 1000000000]
    for i in range(q):
        xi = queries[i]
        x.append(xi)
    # сортируем координаты
    x.sort()
    # считаем количество каждого числа методом двух указателей:
    cnt = []
    i = 0
    while i < len(x):
        j = i
        # двигаем правую границу подотрезка равных элементов:
        while j < len(x) and x[i] == x[j]:
            j += 1
        # полуинтервал [i, j) состоит из чисел, равных x[i]
        cnt.append(j - i)
        i = j
    # удаляем повторы:
    x = list(dict.fromkeys(x))
    # строим двусвязный список:
    Prev = [-1] * len(x)
    Next = [-1] * len(x)
    for i in range(len(x) - 1):
        Prev[i + 1] = i
        Next[i] = i + 1
    # теперь обрабатываем запросы в обратном порядке
    # каждый запрос удаляет ранее добавленный элемент
    answ = [0] * q
    for queryId in range(q - 1, -1, -1):
        # находим и удаляем текущий элемент:
        xi = bisect_left(x, queries[queryId])
        cnt[xi] -= 1
        if cnt[xi] > 0:  # остался повтор
            answ[queryId] = 0
        else:
            # соседи справа и слева:
            ni = Next[xi]
            pi = Prev[xi]
            # расстояние: это минимум из расстояний до соседей:
            answ[queryId] = min(x[ni] - x[xi], x[xi] - x[pi])
            # связываем соседей друг с другом, удаляя xi:
            Prev[ni] = pi
            Next[pi] = ni
    # выводим ответ:
    print(" ".join(map(str, answ)))

tt = int(input())
for _ in range(tt):
    solve()