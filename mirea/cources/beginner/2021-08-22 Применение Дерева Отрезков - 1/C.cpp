#include <bits/stdc++.h>
#define int int64_t
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
const pii neutral = {0,-1};
struct SegTree {
    vpii data;
    SegTree(int n) : data(4*n,neutral) { }
    auto set(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return data[v];
        if (l+1==r) return data[v] = {x,l};
        const int m = (l+r)/2;
        return data[v] = std::max(set(2*v+1,l,m,p,x),set(2*v+2,m,r,p,x));
    }
    auto get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return neutral;
        if (ql <= l && r <= qr) return data[v];
        const int m = (l+r)/2;
        return std::max(get(2*v+1,l,m,ql,qr),get(2*v+2,m,r,ql,qr));
    }
    auto get(int l, int r) {
        return get(0,0,isz(data)/4,l,r+1);
    }
    void set(int p, int x) {
        set(0,0,isz(data)/4,p,x);
    }
};

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, d;
    std::cin >> n >> d;
    vpii order(n);
    for (int i = 0; i < n; i++) {
        int h; std::cin >> h;
        order[i] = {h,i};
    }
    vpii sorted = order;
    std::sort(all(sorted));
    vi whereIt(n), parent(n);
    for (int i = 0; i < n; i++) {
        auto [_,id] = sorted[i];
        whereIt[id] = i;
    }
    SegTree st(n);
    for (auto &[value,index] : order) {
        // нам нужно сделать запрос к подходящим отрезкам
        auto high = std::lower_bound(all(sorted),pii{value+d,0})-sorted.begin();
        auto low  = std::upper_bound(all(sorted),pii{value-d,n})-sorted.begin();
        // [0,low) и [high, n)
        auto [mx,ind] = std::max(st.get(0,low-1),st.get(high,n-1));
        st.set(whereIt[index],mx+1);
        parent[index] = (ind == -1 ? -1 : sorted[ind].second);
    }
    // начинаем восстанавливать ответ
    auto [currMax, index] = st.get(0,n-1);
    int p = sorted[index].second;
    vi answ;
    while (currMax --> 0) {
        answ.push_back(p);
        p = parent[p];
    }
    std::reverse(all(answ));
    std::cout << isz(answ) << '\n';
    for (auto &it : answ) std::cout << it+1 << ' ';
    std::cout << '\n';
    
    return 0;
}