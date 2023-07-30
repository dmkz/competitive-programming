/*
    problem: 1102F. Elongated Matrix
    solution: dynamic programming, bitmasks
*/
#include "template.hpp"
int main() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    vvi a(nRows, vi(nCols));
    std::cin >> a;
    vvi minAbsDiff(nRows, vi(nRows));
    for (int fi = 0; fi < nRows; fi++)
        for (int se = 0; se < nRows; se++)
            if (fi != se) {
                int min = INT_MAX;
                for (int i = 0; i < nCols; i++)
                    remin(min, std::abs(a[fi][i]-a[se][i]));
                minAbsDiff[fi][se] = min;
            }
    if (nRows == 1) {
        // крайний случай
        int k = INT_MAX;
        for (int i = 0; i + 1 < nCols; i++)
            remin(k, std::abs(a[0][i] - a[0][i+1]));
        std::cout << k << std::endl;
        return 0;
    }
    // dp[last][mask] -> OK
    vvi dp(nRows, vi(1 << nRows, INT_MIN));
    auto calcDp = [&](int firstRow, int lastRow)
    {
        std::function<int(int,int)> dfs = [&](int last, int available) -> int
        {
            int cnt = __builtin_popcount(available);
            if (cnt == 1)
                return (last == firstRow ? INT_MAX : INT_MIN);
            if (cnt == 2)
            {
                assert(getbit(available, firstRow) == 1);
                assert(last != firstRow);
                return minAbsDiff[firstRow][last];
            }
            if (dp[last][available] == -1)
            {
                // переберём предыдущего
                int res = INT_MIN;
                for (int prev = 0; prev < nRows; prev++)
                    if (getbit(available,prev) && prev != last &&
                        (cnt == 2 || (cnt > 2 && prev != firstRow))
                    ) {
                        remax(res, std::min(minAbsDiff[last][prev],dfs(prev, available ^ (1 << last))));
                    }
                return (dp[last][available] = res);
            }
            return dp[last][available];
        };
        return dfs(lastRow, (1 << nRows) - 1);
    };
    auto checkCombination = [&](int firstRow, int lastRow) {
        int res = INT_MAX;
        for (int col = 0; col + 1 < nCols; col++) {
            int diff = std::abs(a[firstRow][col+1]-a[lastRow][col]);
            remin(res, diff);
        }
        return std::min(res, calcDp(firstRow, lastRow));
    };
    auto solve = [&]() {
        int res = INT_MIN;
        for (int fi = 0; fi < nRows; fi++)
        {
            dp.assign(nRows, vi(1 << nRows, -1));
            for (int se = 0; se < nRows; se++)
                if (fi != se)
                    remax(res, checkCombination(fi, se));
        }
        return res;
    };
    std::cout << solve() << std::endl;
    return 0;
}
