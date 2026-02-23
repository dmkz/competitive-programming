// перестановки, инверсии, дерево Фенвика
#include <bits/stdc++.h>
using namespace std;
struct Fenwick {
    vector<int> data;
    Fenwick(int n) : data(n, 0) { }
    void inc(int i, int delta) {
        for (; i < (int)data.size(); i |= i + 1)
            data[i] += delta;
    }
    int get(int r) const {
        int res = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            res += data[r];
        return res;
    }
    int get(int l, int r) const {
        return get(r) - get(l-1);
    }
};
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    int64_t answ{};
    for (int i = 0; i < k; i++) {
        Fenwick fenw(n+1);
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            answ += j - fenw.get(x);
            fenw.inc(x, +1);
        }
    }
    cout << answ << endl;
}
