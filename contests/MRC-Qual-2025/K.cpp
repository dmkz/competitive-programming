// Задача: K, Вердикт: OK, Время: 3.029s, Память: 85.59Mb

// Будем поддерживать дерево отрезков, в каждом узле которого дерево фенвика.
// В дереве фенвика будем хранить кол-во элемента: fenw[i] = кол-во i-го элемента
// При добавлении на отрезке наш отрезок [L, R] разбивается на log(n)
// непересекающихся в дереве отрезков узлов. В каждый из которых мы вставляем наш
// элемент. Так как отрезки не пересекаются, то повторов не будет.
// Вставка работает за O(log(n)^2)
// Поиск: на пути от отрезка-листа [p, p] до корня ровно log(n) деревьев фенвика
// в каждом из них сделаем запрос суммы на отрезке. Таким образом мы посчитаем
// количество чисел <= заданного за O(log(n)^2). Добавив бинарный поиск по ответу,
// мы найдём k-ю порядковую статистику за O(log(n)^3)

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int int64_t

void reuniq(auto &x) {
    x.erase(std::unique(all(x)), x.end());
}
int lowpos(const auto &v, const auto &x) {
    return int(std::lower_bound(all(v), x) - v.begin());
}
int uppos(const auto &v, const auto &x) {
    return int(std::upper_bound(all(v), x) - v.begin());
}

using Query = std::tuple<int,int,int,int,int>;

struct Fenwick {
    bool built{false};
    std::vector<int> keys, data;
    void addKey(int key) {
        keys.push_back(key);
    }
    void build() {
        std::sort(all(keys));
        reuniq(keys);
        data.assign(isz(keys), 0);
        built = true;
    }
    void add(int value, int x) {
        assert(built);
        int i = lowpos(keys, value);
        assert(keys[i] == value);
        while (i < isz(data)) {
            data[i] += x;
            i |= i + 1;
        }
    }
    int get(int r) const {
        assert(built);
        r = uppos(keys, r) - 1;
        int res{};
        while (r >= 0) {
            res += data[r];
            r = (r & (r + 1)) - 1;
        }
        return res;
    }
};

struct SegTree {
    int n;
    std::vector<Fenwick> data;
    SegTree(int n_) : n(n_), data(4 * n) { }
    void build() {
        build(0,0,n);
    }
    void build(int v, int l, int r) {
        if (l >= r) return;
        data[v].build();
        if (l + 1 < r) {
            int m = (l+r)/2;
            build(2*v+1,l,m);
            build(2*v+2,m,r);
        }
    }
    void insert(int l, int r, int x, int w) {
        insert(0, 0, n, l, r+1, x, w);
    }
    void insert(int v, int tl, int tr, int l, int r, int x, int w) {
        if (r <= tl || tr <= l || tl >= tr)
            return;
        if (l <= tl && tr <= r) {
            data[v].addKey(x);
            return;
        }
        if (tl + 1 < tr) {
            int m = (tl + tr) / 2;
            insert(2*v+1, tl, m, l, r, x, w);
            insert(2*v+2, m, tr, l, r, x, w);
        }
    }
    void update(int l, int r, int x, int w) {
        update(0, 0, n, l, r+1, x, w);
    }
    void update(int v, int tl, int tr, int l, int r, int x, int w) {
        if (r <= tl || tr <= l || tl >= tr)
            return;
        if (l <= tl && tr <= r) {
            data[v].add(x, w);
            return;
        }
        if (tl + 1 < tr) {
            int m = (tl + tr) / 2;
            update(2*v+1, tl, m, l, r, x, w);
            update(2*v+2, m, tr, l, r, x, w);
        }
    }
    int get(int p, int x) {
        return get(0, 0, n, p, x);
    }
    int get(int v, int tl, int tr, int p, int x) {
        if (p < tl || p >= tr || tl >= tr) return 0;
        assert(tl <= p && p < tr);
        int result = data[v].get(x);
        if (tl + 1 == tr)
            return result;
        int m = (tl + tr) / 2;
        if (p < m) result += get(2 * v + 1, tl, m, p, x);
        else result += get(2 * v + 2, m, tr, p, x);
        return result;
    }
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    std::vector<Query> queries(q);
    SegTree segtree(n);
    for (auto &[t,a,b,c,d] : queries) {
        std::cin >> t;
        if (t == 1) {
            std::cin >> a >> b >> c >> d;
            --a, --b;
            segtree.insert(a, b, c, d);
        } else {
            assert(t == 2);
            std::cin >> a >> b;
            --a;
        }
    }
    segtree.build();
    for (const auto &[t, a, b, c, d] : queries) {
        if (t == 2) {
            int low = 0, high = (int)1e9+1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (segtree.get(a, mid) >= b) high = mid;
                else low = mid;
            }
            std::cout << high << "\n";
        } else {
            assert(t == 1);
            segtree.update(a, b, c, d);
        }
    }
}
