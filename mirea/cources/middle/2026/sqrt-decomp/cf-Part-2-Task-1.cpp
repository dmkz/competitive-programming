#include <bits/stdc++.h>
using namespace std;

const int64_t inf = 1e18L + 100;

struct SqrtDec
{
    
    int gsize, nGroups;
    vector<int64_t> a;
    vector<int64_t> groupMin, groupAdd;
    
    SqrtDec(const vector<int> &a_ = {})
        : gsize(max(1, (int)sqrt((int)a_.size()/2.0)))
        , nGroups(((int)a_.size()+gsize-1)/gsize)
        , a(a_.begin(), a_.end())
        , groupMin(nGroups, +inf)
        , groupAdd(nGroups, 0)
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
        groupMin[gi] = +inf;
        for (int i = gBegin(gi); i < gEnd(gi); i++)
            groupMin[gi] = min(groupMin[gi], a[i]);
    }
    
    void push(int gi) {
        if (groupAdd[gi] == 0)
            return;
        for (int i = gBegin(gi); i < gEnd(gi); i++)
            a[i] += groupAdd[gi];
        groupAdd[gi] = 0;
    }
    
    int64_t getGroupMin(int gi) const {
        return groupMin[gi] + groupAdd[gi];
    }
    
    int64_t getMin(int l, int r) {
        // 0-индексация
        assert(0 <= l && r < size());
        const int gl = l / gsize, gr = r / gsize;
        int64_t answ = inf;
        if (gl == gr) {
            // обновить группу gl
            push(gl);
            for (int i = l; i <= r; i++)
                answ = min(answ, a[i]);
            // пересчитать ответ для группы gl
            buildGroup(gl);
        } else {
            // обновить группы gl и gr
            push(gl); push(gr);
            for (int i = l; i < gEnd(gl); i++)
                answ = min(answ, a[i]);
            for (int j = gl + 1; j < gr; j++)
                answ = min(answ, getGroupMin(j));
            for (int i = gBegin(gr); i <= r; i++)
                answ = min(answ, a[i]);
            // пересчитать ответ для групп gl и gr
            buildGroup(gl); buildGroup(gr);
        }
        return answ;
    }
    
    void add(int l, int r, int x) {
        assert(0 <= l && l <= r && r < size());
        const int gl = l / gsize, gr = r / gsize;
        if (gl == gr) {
            // обновить группу gl
            push(gl);
            for (int i = l; i <= r; i++)
                a[i] += x;
            // пересчитать ответ для группы gl
            buildGroup(gl);
        } else {
            // обновить группы gl и gr
            push(gl); push(gr);
            for (int i = l; i < gEnd(gl); i++)
                a[i] += x;
            for (int j = gl + 1; j < gr; j++)
                groupAdd[j] += x;
            for (int i = gBegin(gr); i <= r; i++)
                a[i] += x;
            // пересчитать ответ для групп gl и gr
            buildGroup(gl); buildGroup(gr);
        }
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q; cin >> n >> q;
    SqrtDec sd(vector<int>(n, 0));
    
    // отвечаем на запросы:
    while (q --> 0) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            r--;
            sd.add(l, r, x);
        } else {
            assert(t == 2);
            int l, r; cin >> l >> r;
            r--;
            cout << sd.getMin(l, r) << '\n';
        }
    }
}
