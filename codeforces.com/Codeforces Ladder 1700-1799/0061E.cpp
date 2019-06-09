/*
    Problem: 61E. Enemy is weak
    
    Solution: Fenwick, sorting, binary search, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
template<typename X, typename Y> int lowpos(const X& x, const Y& y) {
    return int(std::lower_bound(all(x), y) - x.begin());
}
typedef std::vector<int> vi;
struct Fenwick {
    vi data;
    Fenwick(int n) : data(n, 0) { }
    void inc(const int p, int x) {
        for (int i = p; i < isz(data); i |= i + 1) {
            data[i] += x;
        }
    }
    int get(const int r) const {
        int res = 0;
        for (int i = r; i >= 0; i = (i & (i+1))-1) {
            res += data[i];
        }
        return res;
    }
    int get(int l, int r) const {
        return get(r) - (l > 0 ? get(l-1) : 0);
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; std::cout << std::endl) {
        vi x, arr(n);
        for (auto &it : arr) { std::cin >> it; x.push_back(it); }
        std::sort(all(x));
        Fenwick before(n), after(n);
        for (auto& it : arr) {
            it = lowpos(x, it);
            after.inc(it, +1);
        }
        auto answ = 0LL;
        for (auto it : arr) {
            after.inc(it, -1);
            answ += before.get(it+1, n-1) * 1LL * after.get(0, it-1);
            before.inc(it, +1);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}