# структура для системы непересекающихся множеств
class DSU:
    
    def __init__(self, n):
        self.sz = [1] * n;
        self.par = [int(x) for x in range(n)];
        self.numComponents = n;
    
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
            self.numComponents -= 1;

# решение задачи
t = int(input())
for id in range(t):
    n = int(input())
    a = [int(x)-1 for x in input().split()]
    # максимальный ответ: соединим только с теми соседями, которых
    # запомнили. Тогда количество компонент и будет ответом
    dsu = DSU(n);
    for i in range(n):
        dsu.connect(i, a[i]);
    # теперь считаем минимальный ответ
    # есть компоненты-деревья и компоненты-циклы
    # компоненты-циклы нельзя ни с кем соединять
    # компоненты-деревья можем соединить друг с другом
    # получается, минимальный ответ:
    # кол-во компонент-циклов + (есть ли компоненты-деревья)
    # для каждой компоненты посчитаем число уникальных рёбер
    # вычитая количество петель
    uniqEdges = [0] * n;
    isParent = [False] * n;
    for i in range(n):
        pi = dsu.getPar(i);
        uniqEdges[pi] = 2 * dsu.sz[pi];
        isParent[pi] = True;
    # вычитаем петли
    for u in range(n):
        # есть ребро u->a[u]. Проверим, есть ли ребро a[u]->u
        if (a[a[u]] == u): # петля
            uniqEdges[dsu.getPar(u)] -= 1; # вычитаем один раз
                                    # второй раз вычтется симметрично
    # теперь циклы это компонента в которой sz[i] ребёр без петель
    # остальное - деревья
    nCycles, nTrees = 0, 0;
    for i in range(n):
        if isParent[i]:
            if uniqEdges[i] == 2 * dsu.sz[i]:
                nCycles += 1;
            else:
                nTrees += 1;
    # выводим ответ:
    minAnsw = nCycles;
    if nTrees > 0:
        minAnsw += 1;
    maxAnsw = dsu.numComponents;
    print(minAnsw, maxAnsw);