from heapq import heappush, heappop
class Frac:
    __slots__ = ("num", "den")
    def __init__(self, num, den):
        self.num = num
        self.den = den
    def __lt__(self, other):
        return self.num * other.den < other.num * self.den
    def __eq__(self, other):
        return self.num * other.den == other.num * self.den
def solve():
    # можно просто для каждой позиции найти максимальную гору слева (гору с наибольшим углом), потом
    # подставлять значение (b/a) в неравенство. Если для максимума верно, то и для любого другого верно.
    # hj < hi+(xi−xj) * b/a
    # hj-hi < (xi-xj) * (b/a)
    # (hj-hi)/(xi-xj) < (b/a)
    # (hj-hi)/(xi-xj) -> максимум при j < i
    # (h[j2] - h[i])/(x[i] - x[j2]) < (h[j1] - h[i]) / (x[i] - x[j1])
    # (h[j2] - h[i])/(x[j2] - x[i]) > (h[j1] - h[i]) / (x[j1] - x[i])
    # нужно построить выпуклую оболочку и тогда мы найдём максимум для текущей вершины как
    # предыдущую вершину в выпуклой оболочке
    n = int(input())
    x, h = [0] * n, [0] * n
    for i in range(n):
        x[i], h[i] = map(int, input().split())
    # строим выпуклую оболочку
    def isLess(a, b, c, d):
        return (h[b] - h[a]) * (x[d] - x[c]) <= (h[d] - h[c]) * (x[b] - x[a])
    st, prev = [0], [-1] * n
    for k in range(1, n):
        while len(st) > 1:
            i, j = st[-2], st[-1]
            if isLess(i, j, i, k):
                st.pop()
            else:
                break
        prev[k] = st[-1]
        st.append(k)
    # теперь читаем запросы и отслеживаем моменты, когда вершины становятся освещёнными
    # события двух типов: 1) вершина становится освещённой - FLIP, 2) нужно ответить на запрос - ASK
    # события первого типа:
    answ = 1 # первая вершина всегда освещена
    FLIP, ASK = 1, 0
    pq = []
    for k in range(1, n):
        i = prev[k]
        heappush(pq, (Frac(h[i]-h[k], x[k]-x[i]), FLIP, k))
    # события второго типа:
    q = int(input())
    for i in range(q):
        a, b = map(int, input().split())
        heappush(pq, (Frac(b, a), ASK, i))
    # теперь обрабатываем события первого и второго типов в порядке возрастания угла:
    answer = [0] * q
    while pq:
        _, t, id = heappop(pq)
        if t == FLIP:
            answ += 1
        else:
            assert t == ASK
            answer[id] = answ
    print(*answer)
solve()