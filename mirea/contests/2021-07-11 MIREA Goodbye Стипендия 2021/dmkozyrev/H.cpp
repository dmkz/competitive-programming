/*
    Идея: пусть не круг обходит точки, а точка обходит круги. Для этого радиус будет не у курьера, а у елок с белками.
    
    Делаем бинпоиск по радиусу. Для каждой елки нужно теперь знать ее компоненту связности
    
    Между двумя елками есть ребро, если их окружности пересекаются
    
    Курьер не пройдет между двумя парами елок, если есть ребро
    
    Нужно знать, есть ли такая елка у которой в компоненте связности есть путь и в y=200, и в y=-200
    
    Тогда компонента связности этой елки перекрывает путь
    
    Если ни одной такой елки нет, то точка может проскользнуть мимо всей компоненты
*/
#include <bits/stdc++.h>
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using ld = long double;
const ld EPS = 1e-12;
const int YMAX = 200, YMIN = -200;

void setmin(auto &x, auto y) {
    x = (y < x ? y : x);
}

void setmax(auto &x, auto y) {
    x = (y > x ? y : x);
}

struct DSU {
    vi parent,size,ymin,ymax;
    DSU(int n) : parent(n), size(n,1),ymin(n),ymax(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    void setY(int i, int y) {
        ymax[i] = ymin[i] = y;
    }
    int get_par(int u) {
        return u == parent[u] ? u : parent[u] = get_par(parent[u]);
    }
    void connect(int u, int v) {
        u = get_par(u), v = get_par(v);
        if (u == v) return;
        if (size[u] < size[v]) std::swap(u,v);
        setmin(ymin[u],ymin[v]);
        setmax(ymax[u],ymax[v]);
        parent[v] = u;
        size[u] += size[v];
    }
    bool isPathClosed(int u) {
        u = get_par(u);
        return ymin[u] == YMIN && ymax[u] == YMAX;
    }
};
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::setprecision(12);
    int n; std::cin >> n;
    std::vector<pii> vec(n);
    for (auto &[x,y] : vec) {
        std::cin >> x >> y;
    }
    // спроецируем елки на прямые y=200 и y=-200. Это дополнительные препятствия.
    for (int i = 0; i < n; i++) {
        auto [x,y] = vec[i];
        vec.emplace_back(x,YMAX);
        vec.emplace_back(x,YMIN);
    }
    n *= 3;
    ld low = 0, high = YMAX-YMIN;
    while (high - low > EPS) {
        ld mid = (low + high) / 2;
        // нужно проверить, можно ли радиус mid
        // инициализируем систему непересекающихся множеств:
        DSU dsu(n);
        for (int i = 0; i < n; i++) {
            dsu.setY(i,vec[i].second);
        }
        // объединяем множества, получая компоненты связности:
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto [x1,y1] = vec[i];
                auto [x2,y2] = vec[j];
                auto dx = x2-x1;
                auto dy = y2-y1;
                if (dx*dx + dy*dy <= 4 * mid * mid) {
                    dsu.connect(i,j);
                }
            }
        }
        // проверяем, что перекрывающей весь путь компоненты нет (или есть):
        bool ok = true;
        for (int i = 0; ok && i < n; i++) {
            if (dsu.isPathClosed(i))
                ok = false;
        }
        if (ok) low = mid;
        else high = mid;
    }
    std::cout << (low+high)/2 << std::endl;
    return 0;
}