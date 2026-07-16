from bisect import bisect_left

# система непересекающихся множеств: каждому отрезку [l, r) соответствует
# своя вершина в дереве, которая хранит длину этого отрезка
class DSU:
    def __init__(self, n):
        self.par = list(range(n))
        self.len = [0] * n
        self.sz = [1] * n

    # получение представителя с эвристикой сжатия путей:
    def getPar(self, u):
        if u == self.par[u]:
            return u
        self.par[u] = self.getPar(self.par[u])
        return self.par[u]

    # объединение двух множеств с эвристикой по их размеру:
    def merge(self, u, v):
        u = self.getPar(u)
        v = self.getPar(v)
        if u == v:
            return
        if self.sz[u] < self.sz[v]:
            u, v = v, u
        self.sz[u] += self.sz[v]
        self.par[v] = u
        self.len[u] += self.len[v]

    # функции для работы с длиной отрезков:
    def addLen(self, u, x):
        self.len[self.getPar(u)] += x

    def getLen(self, u):
        return self.len[self.getPar(u)]

def solve():
    # читаем запросы, собираем множество используемых координат:
    n, q = map(int, input().split())
    queries = [[0, 0] for _ in range(q)]
    x = [1, n + 1]
    for query in queries:
        c, l, r = input().split()
        query[0] = int(l)
        query[1] = int(r)
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
    # инициализируем DSU, находим лучший ответ после всех запросов:
    dsu = DSU(numSegments)
    best = 0
    for i in range(numSegments):
        if not occupied[i]:
            best = max(best, x[i + 1] - x[i])
            dsu.addLen(i, x[i + 1] - x[i])
    # начинаем обрабатывать запросы в обратном порядке
    # теперь один запрос [l, r] объединяет три отрезка: l-1, l, l+1
    # правая граница не используется, так как в сжатых координатах l == r
    answ = [0] * len(queries)
    for queryId in range(len(queries) - 1, -1, -1):
        # текущее состояние соответствует ответу после queryId-го запроса
        # в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best
        # освобождаем текущий отрезок:
        i = queries[queryId][0]
        dsu.addLen(i, x[i + 1] - x[i])
        occupied[i] = 0
        # объединяем текущий отрезок с его соседом слева:
        if i - 1 >= 0 and not occupied[i - 1]:
            dsu.merge(i - 1, i)
        # объединяем текущий отрезок с его соседом справа:
        if i + 1 < numSegments and not occupied[i + 1]:
            dsu.merge(i, i + 1)
        # обновляем ответ:
        best = max(best, dsu.getLen(i))
    # выводим ответ:
    print(" ".join(map(str, answ)))

tt = int(input())
for _ in range(tt):
    solve()