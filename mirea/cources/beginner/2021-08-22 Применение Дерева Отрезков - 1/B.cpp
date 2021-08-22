#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
struct SegTree {
    std::vector<int> data;
    SegTree(int n) : data(4*n, 0) { }
    auto set(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return data[v];
        if (l+1 == r) return data[v] = x;
        const int m = (l+r)/2;
        return data[v] = std::max(set(2*v+1,l,m,p,x),set(2*v+2,m,r,p,x));
    }
    void set(int p, int x) {
        set(0,0,isz(data)/4,p,x);
    }
    auto getMax(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[v];
        const int m = (l+r)/2;
        return std::max(getMax(2*v+1,l,m,ql,qr),getMax(2*v+2,m,r,ql,qr));
    }
    auto getMax(int l, int r) {
        return getMax(0,0,isz(data)/4,l,r+1);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // нужно уничтожить максимальную последовательность подряд идущих дроидов
    // у такой последовательности есть обязательно начало - начальный дроид
    // давайте для каждого начала найдем максимальный конец
    // что нам нужно? max1(L,R)+max2(L,R)+...+maxM(L,R) <= k
    // при увеличении R максимум может увеличиться
    // максимум для фиксированного L - монотонная функция по R
    // применим два указателя, а максимумы будем считать через дерево отрезков
    int n,m,k; std::cin >> n >> m >> k;
    std::vector<SegTree> segtree(m, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a; std::cin >> a;
            segtree[j].set(i, a);
        }
    }
    // функция для получения вектора из m необходимых количеств выстрелов для отрезка [l,r]
    auto getShots = [&](int l, int r) {
        std::vector<int> answ(m);
        if (l <= r)
            for (int i = 0; i < m; i++) answ[i] = segtree[i].getMax(l,r);
        return answ;
    };
    // функция для получения суммарного необходимого количества выстрелов для отрезка [l,r]
    auto getSumOfMax = [&](int l, int r) {
        int sum = 0;
        for (int it : getShots(l,r)) sum += it;
        return sum;
    };
    // ищем оптимальный ответ двумя указателями:
    int l=0, r=-1, bestL=0, bestR=-1;
    while (l < n) {
        while (r < n && getSumOfMax(l,r+1)<=k) r++;
        if (r - l + 1 > bestR - bestL + 1) {
            bestL = l, bestR = r;
        }
        l++;
    }
    // выводим ответ:
    for (auto it : getShots(bestL,bestR)) std::cout << it << ' ';
    std::cout << std::endl;
}