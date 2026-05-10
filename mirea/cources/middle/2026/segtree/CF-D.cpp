#include <bits/stdc++.h>
using namespace std;
// [l; r] -> [l; r+1)

struct SegTree {
    int n;
    vector<pair<int64_t, int64_t>> data; // 4 * n узлов: {сумма; величина, которую прибавить}
    
    SegTree(int n_ = 0)
        : n(n_)
        , data(4 * n, pair<int64_t, int64_t>{})
    { }
    
    int64_t getValue(int v, int tl, int tr) const {
        auto [s, a] = data[v];
        return s + (tr - tl) * a;
    }
    
    void push(int v, int, int) {
        if (data[v].second == 0)
            return;
        data[2*v+1].second += data[v].second;
        data[2*v+2].second += data[v].second;
        data[v].second = 0;
    }
    
    void pop(int v, int l, int r) {
        int m = (l + r) / 2;
        data[v].first = getValue(2 * v + 1, l, m) + getValue(2 * v + 2, m, r);
    }
    
    int64_t get(int tv, int tl, int tr, int ql, int qr) {
        if (qr <= tl || ql >= tr)
            return 0;
        if (ql <= tl && tr <= qr)
            return getValue(tv, tl, tr);
        int tm = (tl + tr) / 2;
        push(tv, tl, tr);
        auto left = get(2 * tv + 1, tl, tm, ql, qr);
        auto right = get(2 * tv + 2, tm, tr, ql, qr);
        pop(tv, tl, tr);
        return left + right;
    }
    
    int64_t get(int l, int r) {
        return get(0, 0, n, l, r+1);
    }
    
    void update(int tv, int tl, int tr, int ql, int qr, int x) {
        if (qr <= tl || tr <= ql)
            return;
        if (ql <= tl && tr <= qr) {
            data[tv].second += x;
            return;
        }
        int tm = (tl + tr) / 2;
        push(tv, tl, tr);
        update(2 * tv + 1, tl, tm, ql, qr, x);
        update(2 * tv + 2, tm, tr, ql, qr, x);
        pop(tv, tl, tr);
    }
    
    void update(int l, int r, int x) {
        update(0, 0, n, l, r+1, x);
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    SegTree st(n);
    while (q --> 0) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            st.update(l, r-1, x);
        } else {
            assert(t == 2);
            int l, r; cin >> l >> r;
            cout << st.get(l, r-1) << '\n';
        }
    }
}
