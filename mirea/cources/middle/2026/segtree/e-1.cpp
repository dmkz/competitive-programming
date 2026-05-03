#include <bits/stdc++.h>
using namespace std;
// [l; r] -> [l; r+1)

const int inf = (int)1e9 + 1000;

using pii = pair<int, int>; // {значение максимума; его самая левая позиция}

pii combine(pii left, pii right) {
// объединяет два поддерева в одно
    auto [leftMax, leftInd] = left;
    auto [rightMax, rightInd] = right;
    if (leftMax < rightMax)
        return right;
    if (leftMax > rightMax)
        return left;
    return {leftMax, leftInd};
}

struct SegTree {
    int n;
    vector<pii> data; // 4 * n узлов
    
    SegTree(const vector<int> & a)
        : n((int)a.size())
        , data(4 * n, pii{-inf, inf})
    {
        build(0, 0, n, a);
    }
    
    void build(int v, int l, int r, const vector<int> &a) {
        // Узел v на полуинтервале [l; r)
        if (l + 1 == r) {
            // лист [l; l+1)
            data[v] = {a[l], l};
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);
        data[v] = combine(data[2*v+1], data[2*v+2]);
    }
    
    pii get(int tv, int tl, int tr, int ql, int qr) {
        if (ql <= tl && tr <= qr) // [tl; tr) in [ql; qr)
            return data[tv]; // отрезок узла дерева целиком в запросе
        if (qr <= tl || tr <= ql)
            return {-inf, inf}; // отрезок узла дерева вообще не пересекается с запросом
        int tm = (tl + tr) / 2;
        return combine(get(2 * tv + 1, tl, tm, ql, qr),
                       get(2 * tv + 2, tm, tr, ql, qr));
    }
    
    pii get(int l, int r) { // Находит НОД на отрезке [l, r]
        pii result = get(0, 0, n, l, r+1);
        result.second++; // переходим в 1-индексацию
        return result;
    }
    
    void update(int tv, int tl, int tr, int pos, int val) {
        if (pos < tl || pos >= tr) // pos is located outside [tl; tr)
            return;
        if (tl + 1 == tr) {
            // в узел [tl; tl+1) записываем новое значение
            data[tv].first = val;
            return;
        }
        int tm = (tl + tr) / 2;
        update(2 * tv + 1, tl, tm, pos, val);
        update(2 * tv + 2, tm, tr, pos, val);
        data[tv] = combine(data[2*tv+1], data[2*tv+2]);
    }
    
    void update(int pos, int val) {
        update(0, 0, n, pos, val);
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
        //char ch; cin >> ch;
        //if (ch == 'u') {
        //    int pos, x; cin >> pos >> x;
        //    pos--;
        //    st.update(pos, x);
        //} else {
            //assert(ch == 'm');
            int l, r; cin >> l >> r;
            l--, r--;
            auto [val, ind] = st.get(l, r);
            cout << val << ' ' << ind << '\n';
        //}
    }
}
