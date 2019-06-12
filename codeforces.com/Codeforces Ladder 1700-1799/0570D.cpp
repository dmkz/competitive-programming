/*
    Problem: 570D. Tree Requests
    
    Solution: trees, dfs, binary search, bitmasks, prefix sums, O(n + q * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
template<typename X, typename Y> int lowpos(const X& x, const Y& y) {
    return int(std::lower_bound(all(x), y) - x.begin());
}
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
namespace Tree {
    int n, timer;
    vi val,dep,tin,tout;
    vvi next, items, times;
    void init(int n_) {
        n = n_;
        next.assign(1+n,{});
        items = times = next;
        val.assign(1+n,0);
        dep = tin = tout = val;
    }
    void add_edge(int p, int v) {
        next[p].push_back(v);
    }
    void dfs(int u, int d) {        
        tin[u] = timer++;
        items[d].push_back(val[u]);
        times[d].push_back(tin[u]);
        for (int v : next[u]) { dfs(v,d+1); }
        tout[u] = timer++;
    }
    void build() {
        timer = 0;
        dfs(1, 1);
        for (int d = 1; d <= n; d++) {
            for (int i = 1; i < isz(items[d]); i++) {
                items[d][i] ^= items[d][i-1];
            }
        }
    }
    int query(int v, int d) {
        auto l = lowpos(times[d], tin[v]);
        auto r = lowpos(times[d], tout[v]);
        int a = (r > 0 ? items[d][r-1] : 0) ^ (l > 0 ? items[d][l-1] : 0);
        return __builtin_popcount(a) <= 1;
    }
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, q; std::cin >> n >> q; ) {
        Tree::init(n);
        for (int i = 2, p; i <= n; i++) {
            std::cin >> p; Tree::add_edge(p, i);
        }
        std::string s; std::cin >> s;
        for (int i = 1; i <= n; i++) {
            Tree::val[i] = 1 << (s[i-1] - 'a');
        }
        Tree::build();
        while (q--) {
            int v, d; std::cin >> v >> d;
            std::cout << (Tree::query(v,d) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}