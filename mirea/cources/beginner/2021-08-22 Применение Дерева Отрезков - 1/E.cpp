#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define int int64_t
struct SegTree {
    std::vector<int> data;
    SegTree(int n) : data(4*n, 0) { }
    int add(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return data[v];
        if (l + 1 == r) return data[v] += x;
        const int m = (l+r)/2;
        return data[v] = add(2*v+1,l,m,p,x)+add(2*v+2,m,r,p,x);
    }
    int get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[v];
        const int m = (l+r)/2;
        return get(2*v+1,l,m,ql,qr)+get(2*v+2,m,r,ql,qr);
    }
    int add(int p, int x) { return add(0,0,isz(data)/4,p,x); }
    int get(int l, int r) { return get(0,0,isz(data)/4,l,r+1); }
};

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // для начала посчитаем функцию f на каждом префиксе и суффиксе
    std::map<int,int> cnt;
    int n; std::cin >> n;
    std::vector<int> a(n),fPref(n),fSuff(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        fPref[i] = ++cnt[a[i]];
    }
    cnt.clear();
    for (int i = n-1; i >= 0; i--) {
        fSuff[i] = ++cnt[a[i]];
    }
    // теперь нужно посчитать для каждого fPref[i] сколько есть таких j что:
    // fPref[i] > fSuff[j] и i > j
    // для этого используем дерево отрезков на массиве arr[i] = количество сумм равных i
    // теперь ответ для fPref[i] это сумма на отрезке [0,Pref[i]-1] в дереве отрезков
    SegTree st(1+n);
    int answ = 0;
    for (int i = n-1; i >= 0; i--) {
        answ += st.get(0,fPref[i]-1);
        st.add(fSuff[i],1);
    }
    std::cout << answ << std::endl;
    return 0;
}