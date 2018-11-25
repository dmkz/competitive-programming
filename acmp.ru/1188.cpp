/*
    Задача: 1188. Дерево с изменением отрезка
    
    Решение: Дерево Фенвика, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

struct Fenwick {
    
    std::vector<ll> data;

    Fenwick(int n = 0) : data(n) { }
    
    void inc(int p, int x) {
        for (int i = p; i < (int)data.size(); i |= i+1) {
            data[i] += x;
        }
    }
    
    ll get(int r) const {
        ll ret = 0;
        for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
            ret += data[i];
        }
        return ret;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    Fenwick fenwick(1+n+1);
    for (int i = 1, v; i <= n; ++i) {
        std::cin >> v;
        fenwick.inc(  i, +v);
        fenwick.inc(i+1, -v);
    }
    int q; std::cin >> q;
    while (q--) {
        char t; std::cin >> t;
        if (t == 'g') {
            int r; std::cin >> r;
            std::cout << fenwick.get(r) << " ";
        } else {
            int l, r, x; std::cin >> l >> r >> x;
            fenwick.inc(  l,+x);
            fenwick.inc(r+1,-x);
        }
    }
    return 0;
}