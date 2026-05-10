#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<pair<int, int>> data; // 4 * n узлов: {AND; OR}
    
    SegTree(int n_ = 0)
        : n(n_)
        , data(4 * n, pair<int, int>{})
    { }
    
    int getValue(int v, int, int) const {
        auto [AND, OR] = data[v];
        return (OR == 1 ? 1 : AND);
    }
    
    void push(int v, int, int) {
        if (data[v].second == 0)
            return;
        data[2*v+1].second |= data[v].second;
        data[2*v+2].second |= data[v].second;
        data[v].second = 0;
    }
    
    void pop(int v, int l, int r) {
        int m = (l + r) / 2;
        data[v].first = getValue(2 * v + 1, l, m) & getValue(2 * v + 2, m, r);
    }
    
    int get(int tv, int tl, int tr, int ql, int qr) {
        if (qr <= tl || ql >= tr)
            return 1;
        if (ql <= tl && tr <= qr)
            return getValue(tv, tl, tr);
        int tm = (tl + tr) / 2;
        push(tv, tl, tr);
        auto left = get(2 * tv + 1, tl, tm, ql, qr);
        auto right = get(2 * tv + 2, tm, tr, ql, qr);
        pop(tv, tl, tr);
        return left & right;
    }
    
    int get(int l, int r) {
        return get(0, 0, n, l, r+1);
    }
    
    void update(int tv, int tl, int tr, int ql, int qr, int x) {
        if (qr <= tl || tr <= ql)
            return;
        if (ql <= tl && tr <= qr) {
            data[tv].second |= x;
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
    vector st(30, SegTree(n));
    while (q --> 0) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            for (int i = 0; i < 30; i++)
                st[i].update(l, r-1, (x >> i) & 1);
        } else {
            assert(t == 2);
            int l, r; cin >> l >> r;
            int answ = 0;
            for (int i = 0; i < 30; i++)
                answ |= (st[i].get(l, r-1) << i);
            cout << answ << endl;
        }
    }
}
