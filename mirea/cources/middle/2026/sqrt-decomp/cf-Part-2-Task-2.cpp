#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,fma")
using namespace std;

const int mod = (int)1e9+7;

struct SqrtDec
{
    
    int gsize, nGroups;
    vector<int> a;
    vector<int> groupSum, groupMul;
    
    SqrtDec(const vector<int> &a_ = {})
        : gsize(max(1, (int)sqrt((int)a_.size()/6.0)))
        , nGroups(((int)a_.size()+gsize-1)/gsize)
        , a(a_.begin(), a_.end())
        , groupSum(nGroups, 0)
        , groupMul(nGroups, 1)
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
        // построить группу --> вычислить минимум в ней
        groupSum[gi] = 0;
        for (int i = gBegin(gi); i < gEnd(gi); i++)
            (groupSum[gi] += a[i]) %= mod;
    }
    
    void push(int gi) {
        if (groupMul[gi] == 1)
            return;
        for (int i = gBegin(gi); i < gEnd(gi); i++)
            a[i] = int(a[i] * 1LL * groupMul[gi] % mod);
        groupMul[gi] = 1;
    }
    
    int getGroupSum(int gi) const {
        return int(groupSum[gi] * 1LL * groupMul[gi] % mod);
    }
    
    int getSum(int l, int r) {
        // 0-индексация
        assert(0 <= l && r < size());
        const int gl = l / gsize, gr = r / gsize;
        int64_t answ = 0;
        if (gl == gr) {
            // обновить группу gl
            push(gl);
            for (int i = l; i <= r; i++)
                answ += a[i];
            // пересчитать ответ для группы gl
            buildGroup(gl);
        } else {
            // обновить группы gl и gr
            push(gl); push(gr);
            for (int i = l; i < gEnd(gl); i++)
                answ += a[i];
            for (int j = gl + 1; j < gr; j++)
                answ += getGroupSum(j);
            for (int i = gBegin(gr); i <= r; i++)
                answ += a[i];
            // пересчитать ответ для групп gl и gr
            buildGroup(gl); buildGroup(gr);
        }
        return int(answ % mod);
    }
    
    void mul(int l, int r, int x) {
        assert(0 <= l && l <= r && r < size());
        const int gl = l / gsize, gr = r / gsize;
        if (gl == gr) {
            // обновить группу gl
            push(gl);
            for (int i = l; i <= r; i++)
                a[i] = int(a[i] * 1LL * x % mod);
            // пересчитать ответ для группы gl
            buildGroup(gl);
        } else {
            // обновить группы gl и gr
            push(gl); push(gr);
            for (int i = l; i < gEnd(gl); i++)
                a[i] = int(a[i] * 1LL * x % mod);
            for (int j = gl + 1; j < gr; j++)
                groupMul[j] = int(groupMul[j] * 1LL * x % mod);
            for (int i = gBegin(gr); i <= r; i++)
                a[i] = int(a[i] * 1LL * x % mod);
            // пересчитать ответ для групп gl и gr
            buildGroup(gl); buildGroup(gr);
        }
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q; cin >> n >> q;
    SqrtDec sd(vector<int>(n, 1));
    
    // отвечаем на запросы:
    while (q --> 0) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            r--;
            sd.mul(l, r, x);
        } else {
            assert(t == 2);
            int l, r; cin >> l >> r;
            r--;
            cout << sd.getSum(l, r) << '\n';
        }
    }
}
