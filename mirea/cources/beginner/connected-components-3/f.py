# структура для системы непересекающихся множеств
class DSU:
    
    def __init__(self, n):
        self.sz = [1] * n;
        self.par = [int(x) for x in range(n)];
        self.numEdges = [0] * n;
    
    def getPar(self, u):
        if u == self.par[u]:
            return u;
        p = self.getPar(self.par[u]);
        self.par[u] = p;
        return p;
    
    def connect(self, u, v):
        u, v = self.getPar(u), self.getPar(v);
        if u != v:
            if self.sz[u] < self.sz[v]:
                u, v = v, u; # swap
            self.sz[u] += self.sz[v];
            self.par[v] = u;
            self.numEdges[u] += self.numEdges[v];
        self.numEdges[u] += 1;

# решение задачи
# те вершины, которые соединены рёбрами, объединяем в компоненты
# связности, считая при этом количество рёбер в каждой компоненте
# (подсчёт ведётся внутри DSU)
nVert, nEdges = (int(x) for x in input().split())
dsu = DSU(nVert)
for i in range(nEdges):
    u, v = (int(x)-1 for x in input().split())
    dsu.connect(u, v);
# если компонента является циклом (кол-во рёбер равно колву вершин)
# или в ней есть цикл (ребёр больше чем вершин)
# то для неё ответ равен 0: можно по циклу направить рёбра,
# иначе эта компонента является деревом и в этой компоненте ответ
# равен 1, так как будет ровно одна вершина,
# в которую не будет вести ни одно ребро (рёбер на 1 меньше чем вершин)

# отмечаем, какие вершины являются представителями компонент связностей
isParent = [False] * nVert
for i in range(nVert):
    isParent[dsu.getPar(i)] = True
# считаем ответ: количество деревьев
answ = 0
for p in range(nVert):
    if isParent[p]:
        answ += max(0, (dsu.sz[p] - dsu.numEdges[p]))
print(answ)