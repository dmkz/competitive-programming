/*
    Problem: 276E. Little Girl and Problem on Trees
    
    Solution: Segment Tree, Fenwick, trees, dfs, O(n+q*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
struct Node {
    ll sum; int len; ll add;
    Node(ll s_ = 0, int len_ = 0, ll a_ = 0)
        : sum(s_), len(len_), add(a_) { }
    ll value() const { return sum + len * add; }
    Node(Node a, Node b)
        : sum(a.value() + b.value())
        , len(a.len + b.len)
        , add(0) { }
};
struct SegTree {
    int n;
    std::vector<Node> data;
    template<typename T>
    void build(const std::vector<T>& arr) {
        n = isz(arr);
        int sz = 1; while (sz < n) sz *= 2;
        data.resize(2*sz);
        build(0,0,n,arr);
    }
    template<typename T>
    Node build(int v, int l, int r, const std::vector<T>& arr) {
        if (l+1 == r) { return data[v] = Node(arr[l], 1); }
        const int m = (l+r)/2;
        return data[v] = Node(build(2*v+1,l,m,arr),build(2*v+2,m,r,arr));
    }
    void push(int v) {
        if (data[v].add == 0 || data[v].len == 1) { return; }
        data[2*v+1].add += data[v].add;
        data[2*v+2].add += data[v].add;
        data[v].add = 0;
    }
    Node get(int ql, int qr, int v, int tl, int tr) {
        if (qr <= tl || tr <= ql) { return Node(); }
        if (ql <= tl && tr <= qr) { return data[v]; }
        push(v); const int tm = (tl + tr) / 2;
        Node answ(get(ql,qr,2*v+1,tl,tm),get(ql,qr,2*v+2,tm,tr));
        data[v] = Node(data[2*v+1],data[2*v+2]);
        return answ;
    }
    void upd(int ql, int qr, ll x, int v, int tl, int tr) {
        if (qr <= tl || tr <= ql) { return; }
        if (ql <= tl && tr <= qr) { data[v].add += x; return; }
        push(v); const int tm = (tl + tr) / 2;
        upd(ql,qr,x,2*v+1,tl,tm);
        upd(ql,qr,x,2*v+2,tm,tr);
        data[v] = Node(data[2*v+1], data[2*v+2]);
    }
    auto get(int ql, int qr) { return get(ql, qr, 0, 0, n).value(); }
    auto get(int ql) { return get(ql,ql+1); }
    void upd(int ql, int qr, ll x) { upd(ql, qr, x, 0, 0, n); }
};

struct Fenwick {
    int n;
    std::vector<ll> data;
    template<typename T>
    void build(const std::vector<T>& v) {
        data.assign((n = isz(v))+1,0);
        for (int i = 0; i < n; i++) { upd(i,i+1,v[i]); }
    }
    void upd(const int pos, const ll delta) {
        for (int i = pos; i < isz(data); i |= i+1) {
            data[i] += delta;
        }
    }
    void upd(int begin, int after, ll delta) {
        upd(begin, +delta);
        upd(after, -delta);
    }
    ll get(const int pos) const {
        ll res = 0;
        for (int i = pos; i >= 0; i = (i & (i+1))-1) {
            res += data[i];
        }
        return res;
    }
};

template<typename RSQ>
struct Tree {
    int n;
    vvi adj;
    vi id, pos;
    RSQ addToAll;
    std::vector<RSQ> segtrees;
    void init(int n_) {
        n = n_;
        adj.assign(1+n,{});
        id.assign(1+n, 0);
        pos.assign(1+n, 0);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int dfs(int u, int p, int pos_, int id_) {
        id[u] = id_; pos[u] = pos_;
        int cnt = 0, sz = 1;
        for (int v : adj[u]) {
            if (v == p) { continue; }
            cnt++; sz += dfs(v, u, pos_+1, id_);
        }
        assert(cnt <= 1);
        return sz;
    }
    void build() {
        for (int v : adj[1]) {
            int sz = 1 + dfs(v, 1, 1, isz(segtrees));
            segtrees.push_back({});
            segtrees.back().build(std::vector<ll>(sz,0));
        }
        addToAll.build(std::vector<ll>(n,0));
    }
    void add(int v, int x, int d) {
        if (v == 1) { addToAll.upd(0, d+1, x); return; }
        const int i = id[v], p = pos[v];
        int l = p - d, r = p + d;
        r = std::min(r, segtrees[i].n-1);
        if (l <= 1) { addToAll.upd(0, l = -l + 1, x); }
        if (l <= r) { segtrees[i].upd(l,r+1,x); }
    }
    auto get(int v) {
        if (v == 1) { return addToAll.get(0); }
        const int i = id[v], p = pos[v];
        return segtrees[i].get(p) + addToAll.get(p);
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, q; std::cin >> n >> q; std::cout << std::endl) {
        Tree<Fenwick> tree;
        //Tree<SegTree> tree;
        tree.init(n);
        for (int i = 1, u, v; i < n; i++) {
            std::cin >> u >> v;
            tree.add_edge(u,v);
        }
        tree.build();
        while (q--) {
            int t, v, x, d; std::cin >> t >> v;
            if (t == 0) { std::cin >> x >> d; tree.add(v,x,d); }
            else { assert(t == 1); std::cout << tree.get(v) << '\n'; }
        }
    }
    return 0;
}