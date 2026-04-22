#include <bits/stdc++.h>
using namespace std;

// 1) считать сумму на отрезке [L, R]
// 2) прибавлять к i-му элементу значение x

struct SqrtDec
{
    
    int gsize, nGroups;
    vector<int64_t> a;
    vector<int64_t> g;
    
    SqrtDec(const vector<int> &a_ = {})
        : gsize(max(1, (int)sqrt((int)a_.size()/2.0)))
        , nGroups(((int)a_.size()+gsize-1)/gsize)
        , a(a_.begin(), a_.end())
        , g(nGroups, 0)
    {
        for (int i = 0; i < nGroups; i++)
            buildGroup(i);
    }
    
    int size() const {
        return (int)a.size();
    }
    
    int gBegin(int gi) const {
        return gi * gsize;
    }
    
    int gEnd(int gi) const {
        return min(gBegin(gi+1), size());
    }
    
    void buildGroup(int gi) {
        // построить группу --> вычислить сумму в ней
        g[gi] = 0;
        for (int i = gBegin(gi); i < gEnd(gi); i++)
            g[gi] += a[i];
    }
    
    int64_t getSum(int l, int r) const {
        // 0-индексация
        assert(0 <= l && r < size());
        const int gl = l / gsize, gr = r / gsize;
        int64_t answ = 0;
        if (gl == gr) {
            for (int i = l; i <= r; i++)
                answ += a[i];
        } else {
            for (int i = l; i < gEnd(gl); i++) answ += a[i];
            for (int j = gl + 1; j < gr; j++)  answ += g[j];
            for (int i = gBegin(gr); i <= r; i++) answ += a[i];
        }
        return answ;
    }
    
    void add(int pos, int x) {
        // pos в ноль-индексации
        assert(0 <= pos && pos < size());
        g[pos / gsize] += x;
        a[pos] += x;
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    SqrtDec sd(vector<int>(n+1, 0));
    for (int i = 0, ai; i < n; i++) {
        cin >> ai;
        sd.add(i  , +ai);
        sd.add(i+1, -ai);
    }
    
    // отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == 'a') {
            // прибавить на отрезке
            int l, r, x; cin >> l >> r >> x;
            l--, r--;
            sd.add(l  , +x);
            sd.add(r+1, -x);
        } else {
            assert(c == 'g');
            int i; cin >> i;
            i--;
            cout << sd.getSum(0, i) << '\n';
        }
    }
}
