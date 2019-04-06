/*
    Problem: 1119D. Frets On Fire
    
    Solution: dsu, segments, intersection of segments, O((n + q)*(log(n) + log(q)))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define reunique(x) (x).erase(std::unique(all(x)), (x).end())
#define lowpos(x, y) int(std::lower_bound(all(x), (y)) - (x).end())
typedef long long ll;
typedef std::pair<ll,int> pli;
struct DSU {
    std::vector<int> parent, size;
    std::vector<ll> left, len, lastUpdatedAt;
    int cnt; ll sum;
    DSU(int n) : parent(n), size(n, 1), left(n), len(n,0), lastUpdatedAt(n,0), cnt(n), sum(0) {
        for (int i = 0; i < n; ++i) { parent[i] = i; }
    }
    int get_parent(int u) {
        return parent[u] == u ? u : parent[u] = get_parent(parent[u]);
    }
    void union_sets(int u, int v, const ll currLen) {
        u = get_parent(u); v = get_parent(v);
        if (u != v) {
            --cnt;
            if (size[u] < size[v]) { std::swap(u,v); }
            parent[v] = u;
            size[u] += size[v];
            if (lastUpdatedAt[u] < currLen) {
                len[u] += (currLen - lastUpdatedAt[u]);
                lastUpdatedAt[u] = currLen;
            }
            if (lastUpdatedAt[v] < currLen) {
                len[v] += (currLen - lastUpdatedAt[v]);
                lastUpdatedAt[v] = currLen;
            }
            const ll lu = left[u], ru = left[u] + len[u] - 1;
            const ll lv = left[v], rv = left[v] + len[v] - 1;
            const ll ln = std::min(lu, lv), rn = std::max(ru,rv);
            left[u] = ln; len[u] = rn - ln + 1;
            sum = sum - (ru - lu + 1) - (rv - lv + 1) + (rn - ln + 1);
        }
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n, q;
    while (std::cin >> n) {
        std::vector<ll> s(n); 
        for (auto &it : s) { std::cin >> it; }
        std::sort(all(s));
        reunique(s);
        n = isz(s);
        std::set<pli> events;
        for (int i = 0; i+1 < n; ++i) {
            events.insert(pli(s[i+1]-s[i], i));
        }
        DSU dsu(n);
        for (int i = 0; i < n; ++i) { dsu.left[i] = s[i]; }
        std::cin >> q;
        std::map<ll, std::vector<int>> queries;
        for (int i = 0; i < q; ++i) { 
            ll l, r; std::cin >> l >> r; 
            queries[r-l+1].push_back(i); 
        }
        std::vector<ll> answ(q);
        ll currLen = 0;
        for (const auto & record : queries) {
            const ll nextLen = record.first;
            const auto& ids = record.second;
            dsu.sum += dsu.cnt * (nextLen - currLen);
            currLen = nextLen;
            while (isz(events) > 0 && events.begin()->first < currLen) {
                auto front = *events.begin(); events.erase(events.begin());
                dsu.union_sets(front.second, front.second+1, currLen);
            }
            for (auto id : ids) { answ[id] = dsu.sum; }
        }
        for (auto it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}