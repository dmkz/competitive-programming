/*
    Problem: 486E. LIS of Sequence
    Solution: dynamic programming, segment tree, graphs, articular points, O(n log(n))
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
const int INF = (int)1e9;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using pii = std::pair<int,int>;
struct SegTree {
    const int n;
    vi data;
    SegTree(int n_ = 0) : n(n_) {
        int pow2 = 1;
        while (pow2 < n) pow2 *= 2;
        data.assign(2*pow2,-INF);
    }
    int set(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return data[v];
        if (l + 1 == r) return data[v] = x;
        int m = (l + r) / 2;
        return data[v] = std::max(set(2*v+1,l,m,p,x),set(2*v+2,m,r,p,x));
    }
    int max(int v, int l, int r, int ql, int qr) const {
        if (r <= ql || l >= qr) return -INF;
        if (ql <= l && r <= qr) return data[v];
        int m = (l + r) / 2;
        return std::max(max(2*v+1,l,m,ql,qr),max(2*v+2,m,r,ql,qr));
    }
    void set(int p, int x) { set(0,0,n,p,x); }
    int max(int l, int r) const { return max(0,0,n,l,r+1); }
};
const int MX = 100100, NONE = 1, YES = 2, ARTICULAR = 3;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    SegTree segtree(MX);
    vi a(1+n+1), dp(1+n+1), visited(1+n+1), in(1+n+1), answ(1+n+1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    a[0] = 0;
    a[n+1] = MX-1;
    std::vector<std::set<pii>> set(MX);
    for (int i = 0; i < isz(a); i++) {
        int max = std::max(0,segtree.max(0,a[i]-1));
        segtree.set(a[i],dp[i] = max+1);
        set[dp[i]].insert({a[i],i});
    }
    std::priority_queue<int> pq;
    pq.push(n+1);
    int nEdges = 0;
    vvi level(MX);
    for (int i = n+1; i >= 0; i--) {
        assert(dp[i] >= 1);
        if (pq.top() == i) {
            level[dp[i]].push_back(i);
            // process i-th vertex
            auto & s = set[dp[i]-1];
            auto bound = s.lower_bound({a[i],0});
            for (auto it = s.begin(); it != bound; ) {
                auto next = std::next(it);
                const int j = it->second;
                assert(!in[j]);
                pq.push(j);
                in[j] = 1;
                s.erase(it);
                it = next;
            }
            pq.pop();
        } else {
            answ[i] = NONE;
        }
        set[dp[i]].erase({a[i],i});
    }
    for (auto lvl : level) {
        for (auto vert : lvl) {
            answ[vert] = isz(lvl) == 1 ? ARTICULAR : YES;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (answ[i] != NONE && answ[i] != ARTICULAR) {
            answ[i] = YES;
        }
        std::cout << answ[i];
    }
    std::cout << std::endl;
    return 0;
}