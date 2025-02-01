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

# оставить только уникальные элементы в сортированном списке
def unique(s):
    i, p, n = 0, 0, len(s);
    while (i < n):
        j = i;
        while (j < n and s[i] == s[j]):
            j += 1;
        s[p] = s[i];
        i = j;
        p += 1;
    while (n > p):
        s.pop();
        n -= 1;

# вместо хороших будем считать плохие: которые не проходят ни по
# одному чёрному ребру. А затем из всех вычтем их
mod = 10**9+7;
n, k = (int(x) for x in input().split())
dsu = DSU(n);
for i in range(0, n-1):
    u, v, x = (int(x) for x in input().split())
    if (x == 0):
        dsu.connect(u-1, v-1);
# надо найти размеры компонент
# сначала получаем список уникальных представителей компонент
parents = [];
for i in range(0, n):
    parents.append(dsu.getPar(i));
parents.sort();
unique(parents);
# теперь считаем ответ: n**k минус сумма sz[p]**k по каждой компоненте
answ = pow(n, k, mod);
for p in parents:
    answ -= pow(dsu.sz[p], k, mod);
print(answ % mod + mod % mod);