#include <bits/stdc++.h>
#include "FastIO.hpp"

struct Seg { int l, r; };

struct LessByR {
    bool operator()(Seg a, Seg b) {
        return a.r < b.r || (a.r == b.r && a.l < b.l);
    }
};

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    typedef std::vector<int> vi;
    for (int n; fin >> n; fout << '\n') {
        vi a(n); fin >> a;
        std::map<int, std::set<Seg, LessByR>> map;
        for (int l = 0; l < n; ++l) {
            int r = l-1, s = 0;
            while (r+1 < n) {
                s += a[++r];
                map[s].insert(Seg{l+1,r+1});
            }
        }
        std::set<Seg, LessByR> best;
        for (auto &record : map) {
            auto& set = record.second;
            for (auto it = set.begin(); it != set.end(); ) {
                auto next = std::next(it);
                if (next != set.end()) {
                    if (next->l <= it->r) {
                        set.erase(next);
                        continue;
                    }
                }
                it = next;
            }
            if (best.size() < set.size()) { best = set; }
        }
        fout << best.size() << '\n';
        for (auto &it : best) { fout << it.l << ' ' << it.r << '\n'; }
    }
    return 0;
}