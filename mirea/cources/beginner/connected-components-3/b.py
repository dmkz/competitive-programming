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

# создаём систему непересекающихся множеств для 26 букв
dsu = DSU(26);

# читаем данные. каждый ключ соединяет рёбрами буквы, которые
# в него входят. проводим эти рёбра
n = int(input());
used = [False] * 26;
for i in range(n):
    # читаем ключ, сортируем буквы и удаляем повторы
    s = sorted(input());
    unique(s);
    # отмечаем, какие буквы были использованы
    k = len(s);
    for i in range(k):
        used[ord(s[i])-ord('a')] = 1;
    # проводим рёбра
    for i in range(k-1):
        dsu.connect(ord(s[i])-ord('a'), ord(s[i+1])-ord('a'));

# выводим количество компонент связности среди задействованных
# во входных данных латинских букв
parents=[]
for i in range(26):
    if used[i]:
        parents.append(dsu.getPar(i));
parents.sort();
unique(parents);
print(len(parents));