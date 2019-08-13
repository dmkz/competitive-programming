/*
    Problem: 1201D. Treasure Hunting
    Solution: greedy, dynamic programming, binary search, O(n log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
template<typename A, typename B> A& remin(A& a, B b) { return a = (b < a) ? b : a; }
typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;
typedef std::vector<int> vi;
const ll INF = (ll)1e12L;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int nRows, nCols, nPlaces, nLifts;
    while (std::cin >> nRows >> nCols >> nPlaces >> nLifts) {
        std::map<int,int> min, max;
        max[1] = min[1] = 1;
        while (nPlaces--) {
            int r, c; std::cin >> r >> c;
            auto it = max.find(r);
            if (it == max.end()) {
                max[r] = c;
            }
            auto jt = min.find(r);
            if (jt == min.end()) {
                min[r] = c;
            }
            max[r] = std::max(max[r], c);
            min[r] = std::min(min[r], c);
        }
        vvl dp(isz(max), vl(2, INF));
        dp[0][1] = max.begin()->second - min.begin()->second;
        dp[0][0] = 2 * dp[0][1];
        vi lifts(nLifts);
        for (auto &it : lifts) { std::cin >> it; }
        std::sort(all(lifts));
        auto distBetween = [&](int r1, int c1, int r2, int c2) {
            if (r1 == r2) { return 1LL * std::abs(c2-c1); }
            assert(r1 < r2);
            auto next = std::lower_bound(all(lifts), c1);
            ll answ = INF;
            if (next != lifts.end()) {
                answ = std::min(answ, 0LL + std::abs(r2-r1) + std::abs(*next - c1) + std::abs(*next - c2));
            }
            if (next != lifts.begin()) {
                next = std::prev(next);
                answ = std::min(answ, 0LL + std::abs(r2-r1) + std::abs(*next - c1) + std::abs(*next - c2));
            }
            return answ;
        };
        auto currMax = max.begin();
        auto currMin = min.begin();
        for (int lvl = 1; lvl < isz(max); ++lvl) {
            auto prevMax = currMax;
            auto prevMin = currMin;
            currMax++;
            currMin++;
            {
                auto r2 = currMax->first;
                auto c2 = currMax->second;
                {
                    auto r1 = prevMax->first;
                    auto c1 = prevMax->second;
                    remin(dp[lvl][0], 
                        dp[lvl-1][1] + distBetween(r1,c1,r2,c2) + currMax->second - currMin->second);
                }
                {
                    auto r1 = prevMin->first;
                    auto c1 = prevMin->second;
                    remin(dp[lvl][0], 
                        dp[lvl-1][0] + distBetween(r1,c1,r2,c2) + currMax->second - currMin->second);
                }
            }
            {
                auto r2 = currMin->first;
                auto c2 = currMin->second;
                {
                    auto r1 = prevMax->first;
                    auto c1 = prevMax->second;
                    remin(dp[lvl][1], 
                        dp[lvl-1][1] + distBetween(r1,c1,r2,c2) + currMax->second - currMin->second);
                }
                {
                    auto r1 = prevMin->first;
                    auto c1 = prevMin->second;
                    remin(dp[lvl][1], 
                        dp[lvl-1][0] + distBetween(r1,c1,r2,c2) + currMax->second - currMin->second);
                }
            }
        }
        std::cout << std::min(dp.back()[0], dp.back()[1]) << std::endl;
    }
    return 0;
}