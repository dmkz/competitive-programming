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
    
    SegTree(int n_ = 0)
        : n(n_)
        , data(4 * n, pii{-inf, inf})
    { }
    
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
            data[tv] = {val, tl};
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
    SegTree st(n);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        st.update(i, ai);
    }
    int q; cin >> q;
    while (q --> 0) {
        int l, r; cin >> l >> r;
        l--, r--;
        auto [val, ind] = st.get(l, r);
        cout << val << ' ' << ind << '\n';
    }
}
