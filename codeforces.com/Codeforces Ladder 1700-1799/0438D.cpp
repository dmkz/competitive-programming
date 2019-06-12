/*
    Problem: 438D. The Child and Sequence
    
    Solution: segment tree, number theory, O(q * log(n) * log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
#define io_sync_off std::ios_base::sync_with_stdio(0); std::cin.tie(0)
// Debug defines:
#define watch(x) std::cerr << std::setw(12) << #x << " = " << std::setw(12) << x
#define watchln(x) watch(x) << std::endl
#define watchsp(x) watch(x) << " "
#define cerr cerr && debug && std::cerr
const int debug = 0;
namespace std {
    // 2D arrays:
    template<typename T, int N, int M> auto size(const T (&a)[N][M]) { return N * M; }
    template<typename T, int N, int M> auto begin(T (&a)[N][M]) { return &a[0][0]; }
    template<typename T, int N, int M> auto end(T (&a)[N][M]) { return &a[0][0] + N * M; }
    // Algorithms:
    template<typename C> void reuniq(C& c) { c.erase(unique(c), end(c)); }
    template<typename C, typename X> int lowpos(C& c, X& x) {
        return int(lower_bound(all(c), x) - begin(c));
    }
    template<typename X, typename Y> X& remin(X& x, Y& y) { return x = (y < x) ? y : x; }
    template<typename X, typename Y> X& remax(X& x, Y& y) { return x = (x < y) ? y : x; }
}
// Input:
template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto &it : vec) is >> it;
    return is;
}
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<ll> vl;
typedef std::vector<vi> vvi;
typedef std::vector<vl> vvl;
typedef std::pair<int,int> pii;
typedef std::pair<int,ll> pil;
typedef std::pair<ll,int> pli;
typedef std::pair<ll,ll> pll;
// -----------------------------------------------------------------------------
struct Node {
    ll sum; int max, imax;
    Node(ll sum_ = 0, int max_ = -1, int imax_ = -1)
        : sum(sum_), max(max_), imax(imax_) { }
    Node(Node a, Node b) {
        *this = a;
        if (a.max < b.max) { *this = b; }
        sum = a.sum + b.sum;
    }
};
struct SegTree {
    int n;
    std::vector<Node> data;
    SegTree(const vi& arr) {
        n = isz(arr);
        int sz = 1; while (sz < n) sz *= 2;
        data.resize(2*sz);
        build(0,0,n,arr);
    }
    Node build(int v, int l, int r, const vi& arr) {
        if (l + 1 == r) { return data[v] = Node(arr[l], arr[l], l); }
        const int m = (l + r) / 2;
        return data[v] = Node(build(2*v+1,l,m,arr),build(2*v+2,m,r,arr));
    }
    Node get(int ql, int qr, int v, int tl, int tr) {
        if (qr <= tl || tr <= ql) return Node();
        if (ql <= tl && tr <= qr) return data[v];
        const int tm = (tl + tr) / 2;
        return Node(get(ql,qr,2*v+1,tl,tm),get(ql,qr,2*v+2,tm,tr));
    }
    void upd(int p, int x, int v, int tl, int tr) {
        if (p < tl || p >= tr) return;
        if (tl + 1 == tr) { data[v] = Node(x,x,tl); return; }
        const int tm = (tl + tr) / 2;
        upd(p,x,2*v+1,tl,tm);
        upd(p,x,2*v+2,tm,tr);
        data[v] = Node(data[2*v+1],data[2*v+2]);
    }
    void upd(int p, int x) { upd(p, x, 0, 0, n); }
    Node get(int l, int r) { return get(l, r, 0, 0, n); }
};
int main() {
    io_sync_off;
    for (int n, q; std::cin >> n >> q; ) {
        vi arr(n); std::cin >> arr;
        SegTree segtree(arr);
        while (q--) {
            int t; std::cin >> t;
            if (t == 1) {
                int l, r; std::cin >> l >> r;
                std::cout << segtree.get(l-1,r).sum << "\n";
                continue;
            }
            if (t == 2) {
                int l, r, x; std::cin >> l >> r >> x;
                l--;
                Node node;
                while ((node = segtree.get(l,r)).max >= x) {
                    segtree.upd(node.imax, node.max % x);
                }
                continue;
            }
            if (t == 3) {
                int p, x; std::cin >> p >> x;
                segtree.upd(p-1,x);
            }
        }
    }
    return 0;
}