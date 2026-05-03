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
    
    int64_t get(int tv, int tl, int tr, int ql, int qr) {
        if (ql <= tl && tr <= qr) // [tl; tr) in [ql; qr)
            return data[tv]; // отрезок узла дерева целиком в запросе
        if (qr <= tl || tr <= ql)
            return 0; // отрезок узла дерева вообще не пересекается с запросом
        int tm = (tl + tr) / 2;
        return get(2 * tv + 1, tl, tm, ql, qr) +
               get(2 * tv + 2, tm, tr, ql, qr);
    }
    
    int64_t get(int l, int r) { // Находит НОД на отрезке [l, r]
        return get(0, 0, n, l, r+1);
    }
    
    void update(int tv, int tl, int tr, int pos, int val) {
        if (pos < tl || pos >= tr) // pos is located outside [tl; tr)
            return;
        if (tl + 1 == tr) {
            // в узел [tl; tl+1) записываем новое значение
            data[tv] += val;
            return;
        }
        int tm = (tl + tr) / 2;
        update(2 * tv + 1, tl, tm, pos, val);
        update(2 * tv + 2, tm, tr, pos, val);
        data[tv] = data[2*tv+1] + data[2*tv+2];
    }
    
    void update(int pos, int val) {
        update(0, 0, n, pos, val);
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    SegTree st(n+1);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        st.update(i  , +ai);
        st.update(i+1, -ai);
    }
    int q; cin >> q;
    while (q --> 0) {
        char ch; cin >> ch;
        if (ch == 'a') {
            int l, r, x; cin >> l >> r >> x;
            l--, r--;
            st.update(l  , +x);
            st.update(r+1, -x);
        } else {
            assert(ch == 'g');
            int pos; cin >> pos;
            pos--;
            cout << st.get(0, pos) << '\n';
        }
    }
}
