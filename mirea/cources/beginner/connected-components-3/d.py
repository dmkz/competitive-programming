# структура для системы непересекающихся множеств
class DSU:
    
    def __init__(self, n):
        self.sz = [1] * n;
        self.par = [int(x) for x in range(n)];
    
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

# решение задачи: соединяем рёбрами всех друзей в компоненты связности
# затем баним те компоненты, в которых есть хейтеры
n = int(input())
dsu = DSU(n)
numFriendPairs = int(input())
for i in range(numFriendPairs):
    u, v = (int(x) for x in input().split())
    dsu.connect(u-1, v-1);
# если в какой-то компоненте связности есть пара хейтеров
# то нельзя её брать. Сначала отмечаем, какие компоненты вообще есть:
canUseComp = [False] * n;
for i in range(n):
    canUseComp[dsu.getPar(i)] = 1;
# теперь баним те компоненты, в которых есть хейтеры:
numHaters = int(input())
for i in range(numHaters):
    u, v = (int(x) for x in input().split())
    u, v = dsu.getPar(u-1), dsu.getPar(v-1);
    if u == v:
        canUseComp[u] = 0;
# находим ответ: максимальный размер компоненты среди оставшихся
answ = 0;
for i in range(n):
    if canUseComp[i]:
        answ = max(answ, dsu.sz[i]);
print(answ);