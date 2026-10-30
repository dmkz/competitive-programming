# структура данных "система непересекающихся множеств": в каждом поддереве храним размер, представителя,
# а также флаг: есть ли электростанция в данном поддереве или нет. Ответ на задачу будем поддерживать
# и обновлять после каждого запроса.
class DSU:
    def __init__(self,n):
        self.par = list(range(n+1))
        self.sz = [1] * (n+1)
        self.enabled = [False] * (n+1)
        self.answ = 0
    def getPar(self,u):
        if u != self.par[u]:
            self.par[u] = self.getPar(self.par[u])
        return self.par[u]
    # размещение электростанции:
    def enable(self,i):
        i = self.getPar(i)
        self.enabled[i] = True
        self.answ += self.sz[i]
    # проведение ребра и обновление ответа:
    def connect(self,u,v):
        u, v = self.getPar(u), self.getPar(v)
        if u == v: return
        if self.sz[u] < self.sz[v]: u, v = v, u
        if self.enabled[u]: self.answ -= self.sz[u]
        if self.enabled[v]: self.answ -= self.sz[v]
        self.sz[u] += self.sz[v]
        self.par[v] = u
        self.enabled[u] |= self.enabled[v]
        if self.enabled[u]: self.answ += self.sz[u]
def solve():
    # чтение всех данных:
    n, m, k = map(int,input().split())
    p = list(map(int,input().split()))
    edges = []
    for i in range(m):
        u, v = map(int,input().split())
        edges.append((u,v))
    q = int(input())
    queries = list(map(int,input().split()))
    usedEdges = [0] * m
    for i in range(q):
        queries[i] -= 1
        usedEdges[queries[i]] = 1
    # вместо удалений будем рассматривать запросы с конца в начало и добавлять рёбра в граф
    # используем структуру данных "система непересекающихся множеств", которая поддерживает
    # все операции, касающиеся добавления рёбер.
    dsu = DSU(n)
    # устанавливаем электростанции:
    for i in p:
        dsu.enable(i)
    # проводим рёбра, которые никогда не будут удалены:
    for i in range(m):
        if not usedEdges[i]:
            u, v = edges[i]
            dsu.connect(u,v)
    # теперь добавляем рёбра с конца в начало:
    answ = []
    for i in range(q-1,-1,-1):
        answ.append(dsu.answ)
        id = queries[i]
        u, v = edges[id]
        dsu.connect(u,v)
    # выводим ответ:
    print(*answ[::-1])
solve()