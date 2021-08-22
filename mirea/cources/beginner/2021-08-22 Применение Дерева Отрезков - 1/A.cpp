#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
// в задаче используется идея дерева отрезков, но функция зависит от глубины узла
// на самом последнем уровне всегда берется OR, и на всех уровнях, которые совпадают с ним
// по чётности. используем это
struct SegTree {
    std::vector<int> data;
    SegTree(int n) : data(4*n) { }
    auto merge(int height, auto left, auto right) {
        return height % 2 == 0 ? (left | right) : (left ^ right);
    }
    auto set(int v, int l, int r, int p, int x, int height) {
        if (p < l || p >= r) return data[v];
        if (l + 1 == r) return data[v] = x;
        const int m = (l+r)/2;
        return data[v] = merge(height, set(2*v+1,l,m,p,x,height-1), set(2*v+2,m,r,p,x,height-1));
    }
    auto set(int p, int x, int height) {
        return set(0,0,isz(data)/4,p,x,height);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    SegTree st(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        int a; std::cin >> a;
        st.set(i,a,n+1);
    }
    while (q --> 0) {
        int i,a; std::cin >> i >> a;
        std::cout << st.set(i-1,a,n+1) << '\n';
    }
}