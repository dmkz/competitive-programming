/*
    Problem: 242C. King's Path
    
    Solution: bfs, graphs, grid graph, shortest path, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define reunique(x) (x).erase(std::unique(all(x)),(x).end())
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
struct Pair {
    int r, c; 
    Pair(int r_ = 0, int c_ = 0) : r(r_), c(c_) { }
};
bool operator<(const Pair& a, const Pair& b) {
    return a.r < b.r || (a.r == b.r && a.c < b.c);
}
template<typename T> bool operator>(const T& a, const T& b) { return b < a; }
template<typename T> bool operator>=(const T& a, const T& b) { return !(a < b); }
template<typename T> bool operator<=(const T& a, const T& b) { return !(a > b); }
template<typename T> bool operator!=(const T& a, const T& b) { return a < b || b < a; }
template<typename T> bool operator==(const T& a, const T& b) { return !(a != b); }
template<typename T, typename X>
int lowpos(const T& vec, const X& item) {
    return int(std::lower_bound(all(vec), item) - (vec).begin());
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int r0, c0, r1, c1;
    while (std::cin >> r0 >> c0 >> r1 >> c1) {
        // Input:
        std::vector<Pair> pt;
        int q, total = 0; std::cin >> q;
        while (q--) {
            int r, begin, end; std::cin >> r >> begin >> end;
            total += end - begin + 1;
            assert(total <= 100000);
            for (int c = begin; c <= end; ++c) {
                pt.push_back(Pair(r,c));
            }
        }
        // Sort and erase repeated:
        std::sort(all(pt));
        reunique(pt);
        // Start bfs:
        std::queue<int> queue;
        vi dist(isz(pt), -1);
        int s = lowpos(pt, Pair(r0,c0));
        assert(s < isz(pt) && pt[s] == Pair(r0,c0));
        dist[s] = 0;
        queue.push(s);
        // Main cycle of bfs:
        while (!queue.empty()) {
            auto id = queue.front(); queue.pop();
            const auto& p = pt[id];
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr * dr + dc * dc == 0) { continue; }
                    auto what = Pair(p.r + dr, p.c + dc);
                    auto nt = lowpos(pt, what);
                    if (nt < isz(pt) && pt[nt] == what && dist[nt] == -1) {
                        dist[nt] = dist[id]+1;
                        queue.push(nt);
                    }
                }
            }
        }
        int t = lowpos(pt, Pair(r1,c1));
        assert(t < isz(pt) && pt[t] == Pair(r1,c1));
        std::cout << dist[t] << '\n';
    }
    return 0;
}