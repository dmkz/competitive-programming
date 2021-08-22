#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define int int64_t
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
using ld = long double;
const ld pi = std::acos(ld(-1));
struct SegTree {
    std::vector<int> data;
    SegTree(int n) : data(4*n, 0) { }
    int set(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return data[v];
        if (l + 1 == r) return data[v] = x;
        const int m = (l+r)/2;
        return data[v] = std::max(set(2*v+1,l,m,p,x),set(2*v+2,m,r,p,x));
    }
    
    int get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[v];
        const int m = (l+r)/2;
        return std::max(get(2*v+1,l,m,ql,qr),get(2*v+2,m,r,ql,qr));
    }
    int set(int p, int x) { return set(0,0,isz(data)/4,p,x); }
    int get(int l, int r) { return get(0,0,isz(data)/4,l,r+1); }
};

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(9);
    // объем цилиндра равен pi * r^2 * h
    // сумма объемов цилиндров равна pi * (r[1] * r[1] * h[1] + ... + r[k] * r[k] * h[k])
    // поэтому будем использовать величину r^2 * h в качестве объема - целочисленную,
    // а затем умножим на pi
    // допустим мы рассматриваем i-й цилиндр и все [0, i-1] уже обработали
    // тогда нужно найти максимальный ответ для каждого цилиндра на отрезке [0, i-1]
    // а дальше взять максимум по всем, которые по объему меньше, чем v[i], и прибавить v[i]
    // чтобы сделать быстрее квадрата нужно, чтобы все меньшие объемы образовывали
    // непрерывный подотрезок: тогда сможем использовать дерево отрезков!
    // посчитаем все объемы, отсортируем их и в дереве отрезков будем хранить ответы
    // для каждого объема, но в отсортированном по объемам порядке
    int n; std::cin >> n;
    vpii v(n);
    for (int i = 0, r, h; i < n; i++) {
        std::cin >> r >> h;
        v[i] = {r*r*h,i};
    }
    auto sorted = v;
    std::sort(all(sorted));
    vi whereIt(n);
    for (int i = 0; i < n; i++) {
        whereIt[sorted[i].second] = i;
    }
    SegTree st(n);
    int answ = 0;
    for (auto &[value, index] : v) {
        auto right = std::lower_bound(all(sorted),pii{value,0})-sorted.begin();
        auto mx = st.get(0,right-1);
        answ = std::max(answ,st.set(whereIt[index],mx+value));
    }
    std::cout << answ * pi << std::endl;
    return 0;
}