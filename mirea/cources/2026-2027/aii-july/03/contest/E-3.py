from bisect import bisect_left

def solve():
    # читаем запросы, собираем множество используемых координат:
    n, q = map(int, input().split())
    queries = [[0, 0] for _ in range(q)]
    x = [1, n + 1]
    for query in queries:
        c, l, r = input().split()
        query[0], query[1] = int(l), int(r)
        x.append(query[0])
        x.append(query[1] + 1)
    # делаем сжатие координат:
    x = sorted(set(x))
    # отмечаем, какие отрезки заняты после всех запросов:
    numSegments = len(x) - 1
    occupied = [0] * numSegments
    for query in queries:
        query[0] = bisect_left(x, query[0])
        occupied[query[0]] = 1
    # строим двусвязный список занятых отрезков и находим лучший ответ
    # после всех запросов:
    Prev = [-1] * numSegments
    Next = [numSegments] * numSegments
    best = 0
    prevOccupied = -1
    for i in range(numSegments):
        if not occupied[i]:
            continue
        best = max(best, x[i] - x[prevOccupied + 1])
        Prev[i] = prevOccupied
        if prevOccupied != -1:
            Next[prevOccupied] = i
        prevOccupied = i
    best = max(best, x[numSegments] - x[prevOccupied + 1])
    # начинаем обрабатывать запросы в обратном порядке
    # теперь один запрос [l, r] удаляет один занятый отрезок и соединяет
    # два соседних свободных промежутка в один
    answ = [0] * len(queries)
    for queryId in range(len(queries) - 1, -1, -1):
        # текущее состояние соответствует ответу после queryId-го запроса
        # в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best
        # удаляем текущий занятый отрезок:
        i = queries[queryId][0]
        # соседи справа и слева среди ещё занятых отрезков:
        ni, pi = Next[i], Prev[i]
        # связываем соседей друг с другом, удаляя i:
        if pi != -1:
            Next[pi] = ni
        if ni != numSegments:
            Prev[ni] = pi
        # новый свободный промежуток ограничен занятыми соседями:
        best = max(best, x[ni] - x[pi + 1])
    # выводим ответ:
    print(" ".join(map(str, answ)))

tt = int(input())
for _ in range(tt):
    solve()