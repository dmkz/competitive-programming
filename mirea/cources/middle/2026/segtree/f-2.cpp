#include <bits/stdc++.h>
using namespace std;
// [l; r] -> [l; r+1)

struct SegTree {
    int n;
    vector<int64_t> data; // 4 * n узлов
    
    SegTree(int n_ = 0)
        : n(n_)
        , data(4 * n, 0)
    { }
    
    int64_t get(int tv, int tl, int tr, int pos) {
        if (pos < tl || pos >= tr)
            return 0;
        if (tl + 1 == tr)
            return data[tv];
        int tm = (tl + tr) / 2;
        return get(2 * tv + 1, tl, tm, pos) +
               get(2 * tv + 2, tm, tr, pos) + data[tv];
    }
    
    int64_t get(int pos) {
        return get(0, 0, n, pos);
    }
    
    void update(int tv, int tl, int tr, int ql, int qr, int x) {
        if (qr <= tl || tr <= ql)
            return;
        if (ql <= tl && tr <= qr) {
            data[tv] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        update(2 * tv + 1, tl, tm, ql, qr, x);
        update(2 * tv + 2, tm, tr, ql, qr, x);
        //data[tv] = data[2*tv+1] + data[2*tv+2];
    }
    
    void update(int l, int r, int x) {
        update(0, 0, n, l, r+1, x);
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    SegTree st(n);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        st.update(i, i, ai);
    }
    int q; cin >> q;
    while (q --> 0) {
        char ch; cin >> ch;
        if (ch == 'a') {
            int l, r, x; cin >> l >> r >> x;
            l--, r--;
            st.update(l, r, x);
        } else {
            assert(ch == 'g');
            int pos; cin >> pos;
            pos--;
            cout << st.get(pos) << '\n';
        }
    }
}
