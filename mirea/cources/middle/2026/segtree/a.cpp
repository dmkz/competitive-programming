#include <bits/stdc++.h>
using namespace std;
// [l; r] -> [l; r+1)

int myGCD(int a, int b) {
    return (b == 0 ? a : myGCD(b, a % b));
}

struct SegTree {
    int n;
    vector<int> data; // 4 * n узлов
    
    SegTree(const vector<int> & a)
        : n((int)a.size())
        , data(4 * n, 0)
    {
        build(0, 0, n, a);
    }
    
    void build(int v, int l, int r, const vector<int> &a) {
        // Узел v на полуинтервале [l; r)
        if (l + 1 == r) {
            // лист [l; l+1)
            data[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);
        data[v] = myGCD(data[2*v+1], data[2*v+2]);
    }
    
    int get(int tv, int tl, int tr, int ql, int qr) {
        if (ql <= tl && tr <= qr) // [tl; tr) in [ql; qr)
            return data[tv]; // отрезок узла дерева целиком в запросе
        if (qr <= tl || tr <= ql)
            return 0; // отрезок узла дерева вообще не пересекается с запросом
        int tm = (tl + tr) / 2;
        int la = get(2 * tv + 1, tl, tm, ql, qr);
        int ra = get(2 * tv + 2, tm, tr, ql, qr);
        return myGCD(la, ra);
    }
    
    int get(int l, int r) { // Находит НОД на отрезке [l, r]
        return get(0, 0, n, l, r+1);
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    SegTree st(a);
    int q; cin >> q;
    while (q --> 0) {
        int l, r; cin >> l >> r;
        l--, r--;
        cout << st.get(l, r) << '\n';
    }
}
