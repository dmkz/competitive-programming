#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

const int mod = (int)1e9+7;

int add(int a, int b) {
    return (a + b) % mod;
}

int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}

void mulby(int &a, int b) {
    a = mul(a, b);
}

struct SegTree {
    int n;
    vector<pair<int, int>> data; // 4 * n узлов: {SUM; MUL}
    
    SegTree(const vector<int> &a)
        : n((int)a.size())
        , data(4 * n, pair<int, int>(0, 1))
    {
        build(0, 0, n, a);
    }
    
    void build(int v, int l, int r, const vector<int> &a) {
        if (l + 1 == r) {
            data[v] = {a[l] % mod, 1};
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);
        pop(v, l, r);
    }
    
    int getValue(int v, int, int) const {
        auto [SUM, MUL] = data[v];
        return mul(SUM, MUL);
    }
    
    void push(int v, int, int) {
        if (data[v].second == 1)
            return;
        mulby(data[2*v+1].second, data[v].second);
        mulby(data[2*v+2].second, data[v].second);
        data[v].second = 1;
    }
    
    void pop(int v, int l, int r) {
        int m = (l + r) / 2;
        data[v].first = add(getValue(2 * v + 1, l, m), getValue(2 * v + 2, m, r));
    }
    
    int get(int tv, int tl, int tr, int ql, int qr) {
        if (qr <= tl || ql >= tr)
            return 0;
        if (ql <= tl && tr <= qr)
            return getValue(tv, tl, tr);
        int tm = (tl + tr) / 2;
        push(tv, tl, tr);
        auto left = get(2 * tv + 1, tl, tm, ql, qr);
        auto right = get(2 * tv + 2, tm, tr, ql, qr);
        pop(tv, tl, tr);
        return add(left, right);
    }
    
    int get(int l, int r) {
        return get(0, 0, n, l, r+1);
    }
    
    void update(int tv, int tl, int tr, int ql, int qr, int x) {
        if (qr <= tl || tr <= ql)
            return;
        if (ql <= tl && tr <= qr) {
            mulby(data[tv].second, x);
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
    SegTree st(vector<int>(n, 1));
    while (q --> 0) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            st.update(l, r-1, x);
        } else {
            assert(t == 2);
            int l, r; cin >> l >> r;
            cout << st.get(l, r-1) << endl;
        }
    }
}
