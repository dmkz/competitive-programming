/*
    Problem: 383C. Propagating tree
    
    Solution: fenwick, euler tour, trees, O((n + q) * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vl;
struct Fenwick {
    vl data;
    void inc(int p, int delta) {
        for (int i = p; i < isz(data); i |= i+1) {
            data[i] += delta;
        }
    }
    void inc(int begin, int after, int delta) {
        inc(begin, +delta);
        inc(after, -delta);
    }
    ll get(int pos) const {
        ll res = 0;
        for (int i = pos; i >= 0; i = (i & (i + 1))-1) {
            res += data[i];
        }
        return res;
    }
    template<typename T>
    Fenwick(const std::vector<T>& vec) : data(isz(vec)+1) {
        for (int i = 0; i < isz(vec); i++) {
            inc(i,i+1,vec[i]);
        }
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int nV, nQ;
    std::cin >> nV >> nQ;
    vi arr(1+nV);
    for (int i = 1; i <= nV; i++) { std::cin >> arr[i]; }
    vvi adj(1+nV);
    for (int i = 1, u, v; i < nV; i++) {
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vi beginOdd(1+nV), afterOdd(1+nV), beginEven(1+nV), afterEven(1+nV), depth(1+nV);
    vi odd, even;
    std::function<void(int,int,int)> euler_tour = [&](int u, int p, int d) {
        depth[u] = d;
        beginOdd[u] = isz(odd);
        beginEven[u] = isz(even);
        if (d % 2 == 0) { even.push_back(arr[u]); }
        else { odd.push_back(arr[u]); }
        for (int v : adj[u]) {
            if (v == p) { continue; }
            euler_tour(v,u,d+1);
        }
        afterOdd[u] = isz(odd);
        afterEven[u] = isz(even);
    };
    euler_tour(1,0,0);
    Fenwick fenwick_odd(odd), fenwick_even(even);
    while (nQ--) {
        int t; std::cin >> t;
        if (t == 1) {
            int vert, delta; std::cin >> vert >> delta;
            int toOdd = (depth[vert] % 2 == 1) ? delta : -delta;
            int toEven = (depth[vert] % 2 == 0) ? delta : -delta;
            fenwick_odd.inc(beginOdd[vert], afterOdd[vert], toOdd);
            fenwick_even.inc(beginEven[vert], afterEven[vert], toEven);
        } else {
            int vert; std::cin >> vert;
            auto & fenwick = (depth[vert] % 2 == 0 ? (fenwick_even) : (fenwick_odd));
            auto pos = (depth[vert] % 2 == 0 ? beginEven[vert] : beginOdd[vert]);
            std::cout << fenwick.get(pos) << "\n";
        }
    }
    return 0;
}