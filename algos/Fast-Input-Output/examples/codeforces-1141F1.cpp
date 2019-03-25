#include <bits/stdc++.h>
#include "FastIO.hpp"

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    typedef std::vector<int> vi;
    typedef std::pair<int,int> pii;
    #define all(x) (x).begin(), (x).end()
    struct Seg { int l, r, sum; };
    for (int n; fin >> n; fout << '\n') {
        vi a(n);
        fin >> a;
        std::vector<Seg> segs;
        for (int l = 0; l < n; ++l) {
            int r = l-1, s = 0;
            while (r+1 < n) {
                s += a[++r];
                segs.push_back(Seg{l+1,r+1,s});
            }
        }
        std::stable_sort(all(segs), [](Seg lhs, Seg rhs) { return lhs.r < rhs.r; });
        std::vector<pii> dp(segs.size(), pii(0,-1));
        for (int i = 0; i < (int)segs.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (segs[j].sum == segs[i].sum && segs[j].r < segs[i].l) {
                    dp[i] = std::max(dp[i], pii(dp[j].first+1, j));
                }
            }
            dp[i] = std::max(dp[i], pii(1, i));
        }
        int last = (int)(std::max_element(all(dp)) - dp.begin());
        std::vector<Seg> answ;
        answ.push_back(segs[last]);
        while (last != dp[last].second) {
            last = dp[last].second;
            answ.push_back(segs[last]);
        }
        fout << answ.size() << '\n';
        for (auto &p : answ) { fout << p.l << ' ' << p.r << '\n'; }
    }
    return 0;
}