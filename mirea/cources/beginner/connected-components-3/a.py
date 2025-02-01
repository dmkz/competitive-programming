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

# пробегаемся по всем подстрокам длины k и проводим рёбра
# между позициями символов, которые должны быть равны
# это означает, что на позициях, соединённых рёбрами, должны стоять
# одинаковые символы. Компонента связности содержит все позиции
# символов, которые должны быть попарно-равны между собой
n,m,k = (int(x) for x in input().split())
dsu = DSU(n);
for start in range(0,n-k+1):
    for i in range(0,k//2):
        dsu.connect(start+i, start+k-1-i);
# теперь считаем количество различных компонент
parents = [];
for i in range(0, n):
    parents.append(dsu.getPar(i));
parents.sort();
unique(parents);
# выводим ответ: для каждой компоненты можем выбрать один из m символов
# произвольно, поэтому ответ равен m в степени количества компонент:
print(pow(m,len(parents),1000000007));