#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
struct SegTree {
    vector<int> data;
    SegTree(int n) : data(4*n, 0) { }
    void set(int p, int x) { set(0,0,isz(data)/4,p,x); }
    int get(int l, int r) { return r < l ? 0 : get(0,0,isz(data)/4,l,r+1); }
    int lower_bound(int givenSum) { return lower_bound(0,0,isz(data)/4,givenSum); }
private:
    int set(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return data[v];
        if (l + 1 == r) return data[v] = x;
        int m = (l+r)/2;
        return data[v] = set(2*v+1,l,m,p,x)+set(2*v+2,m,r,p,x);
    }
    int get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[v];
        int m = (l+r)/2;
        return get(2*v+1,l,m,ql,qr)+get(2*v+2,m,r,ql,qr);
    }
    // найти самый первый элемент R, для которого givenSum <= get(0,R)
    int lower_bound(int v, int l, int r, int givenSum) {
        if (l + 1 == r) return givenSum <= data[v] ? l : r;
        int m = (l + r) / 2;
        if (givenSum <= data[2*v+1]) return lower_bound(2*v+1,l,m,givenSum);
        else return lower_bound(2*v+2,m,r,givenSum-data[2*v+1]);
    }
};
int main() {
    freopen("joseph.in", "rt", stdin);
    freopen("joseph.out", "wt", stdout);
    int n, step; cin >> n >> step;
    SegTree st(1+n);
    // изначально все чуваки под номерами 1 ... n стоят в кругу:
    for (int i = 1; i <= n; i++) {
        st.set(i, 1);
    }
    // начинаем их вычёркивать:
    for (int i = 1, p = 1; i < n; ++i) {
        // p - текущая позиция, откуда отсчитываем step вправо чуваков
        int s = step;
        int rem = st.get(p,n);
        if (rem < s) {
            // если сделаем шаг, то улетим за пределы массива, поэтому нужно
            // перейти в начало массива, уменьшив необходимый шаг
            s -= rem;
            p = 1;
            // учитываем периодичность:
            int t = st.get(p, n);
            s %= t;
            if (s == 0) s = t;
        }
        p = st.lower_bound(s+st.get(0,p-1));
        // чувак под номером p выбывает
        st.set(p,0);
    }
    cout << st.lower_bound(1) << endl;
}