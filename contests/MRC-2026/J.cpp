#include <bits/stdc++.h>
#include <bits/extc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int int64_t
using pii = std::pair<int,int>;
int lowpos(const auto &v, const auto &x) {
    return int(std::lower_bound(all(v), x) - v.begin());
}
struct SegTree {
    std::vector<int> data;
    SegTree(int n) : data(4*n, 0) { }
    void add(int p, int x) {
        add(0, 0, isz(data)/4, p, x);
    }
    int sum(int l, int r) const {
        return sum(0, 0, isz(data)/4, l, r+1);
    }
    int operator()(int l, int r) const {
        return sum(l, r);
    }
    void add(int v, int tl, int tr, int p, int x) {
        if (p < tl || p >= tr) return;
        if (tl + 1 == tr) {
            data[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        add(2*v+1, tl, tm, p, x);
        add(2*v+2, tm, tr, p, x);
        data[v] = data[2*v+1] + data[2*v+2];
    }
    int sum(int v, int tl, int tr, int ql, int qr) const {
        if (qr <= tl || ql >= tr) return 0;
        if (ql <= tl && tr <= qr) return data[v];
        int tm = (tl + tr) / 2;
        return sum(2*v+1, tl, tm, ql, qr) + sum(2*v+2, tm, tr, ql, qr);
    }
};
void solve() {
    // читаем входные данные:
    int n, s, c; std::cin >> n >> s >> c;
    std::vector<int> a(n);
    for (auto &it : a) std::cin >> it;
    std::string b; std::cin >> b;
    // раскладываем товары в три различных вектора по типам, а также в объединённый вектор:
    std::vector<pii> fi, se, th, coords;
    for (int i = 0; i < n; i++) {
        if (b[i] == 'M') fi.emplace_back(a[i], i);
        else if (b[i] == 'S') se.emplace_back(a[i], i);
        else { assert(b[i] == 'D'); th.emplace_back(a[i], i); }
        coords.emplace_back(a[i], i);
    }
    // сортируем:
    std::sort(all(coords));
    std::sort(all(fi));
    std::sort(all(se));
    std::sort(all(th));
    // сжимаем координаты и строим дерево отрезков поверх объединённого вектора всех товаров:
    SegTree segTreeSum(isz(coords));
    SegTree segTreeCnt(isz(coords));
    auto insert = [&](auto x) { // вставка товара
        const int ix = lowpos(coords, x);
        segTreeSum.add(ix, +x.first);
        segTreeCnt.add(ix, +1);
    };
    auto remove = [&](auto x) { // удаление товара
        const int ix = lowpos(coords, x);
        segTreeSum.add(ix, -x.first);
        segTreeCnt.add(ix, -1);
    };
    // сперва вставляем туда все элементы:
    for (const auto &it : coords) insert(it);
    // теперь перебираем все варианты для фиксированного количества акций "три по c"
    // если мы использовали акцию 0 раз, то мы берём k самых дешёвых товаров суммой <= s
    // если мы использовали акцию 1 раз, то нам выгодно купить самый дорогой товар каждого
    // типа, удалить их из дерева отрезков как доступные для покупки, а затем снова купить
    // k самых дешёвых товаров суммой <= s. Так перебираем все варианты и находим лучший
    int answ = 0, best = 0, pref = 0;
    for (const auto &[x, _] : coords)
        if (pref+x <= s) pref += x, best++;
        else break;
    // применяем акцию, пока можем, и считаем лучший вариант для заданного количества акций:
    while ((isz(fi) || isz(se) || isz(th)) && s >= c) {
        // удаляем три самых дорогих товара: включаем их в акцию
        if (isz(fi)) {
            auto item = fi.back();
            fi.pop_back();
            answ++;
            remove(item);
        }
        if (isz(se)) {
            auto item = se.back();
            se.pop_back();
            answ++;
            remove(item);
        }
        if (isz(th)) {
            auto item = th.back();
            th.pop_back();
            answ++;
            remove(item);
        }
        s -= c;
        // теперь бинарным поиском находим, какое максимальное количество товаров можем купить
        // за оставшиеся деньги по одному:
        int low = -1, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (segTreeSum(0, mid) > s) high = mid;
            else low = mid;
        }
        // low - крайний элемент, для которого sum(0, low) <= S
        best = std::max(best, answ + segTreeCnt(0, low));
    }
    std::cout << best << std::endl;
}
int32_t main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int tt = 1; std::cin >> tt;
    while (tt --> 0) solve();
    return 0;
}