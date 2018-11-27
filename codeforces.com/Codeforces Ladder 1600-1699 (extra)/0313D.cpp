/*
    Problem: 313D. Ilya and Roads
    
    Solution: dynamic programming, O(n^3+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#define remin(x, y) if ((x) > (y)) (x) = (y)

typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;

const ll INF = (ll)1e18L;

struct Triple {
    int lt, rt, cost;
};

ll solve(int n, const std::vector<Triple>& triples, int minCnt) {
    vvl minFrom(n, vl(1+n, INF)); // minFrom[r][len] -> min_cost
    for (int i = 0; i < n; ++i) {
        minFrom[i][0] = 0;
    }
    for (const auto& t : triples) {
        remin(minFrom[t.rt][t.rt-t.lt+1], t.cost);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j >= 0; --j) {
            remin(minFrom[i][j], minFrom[i][j+1]);
        }
    }
    vvl minSum(1+n, vl(1+n, INF)); // minSum[prefixLen][cntOnPrefix] --> min possible sum
    minSum[0][0] = 0;
    for (int len = 1; len <= n; ++len) {
        int pos = len - 1;
        for (int cntR = 0; cntR <= len; ++cntR) {
            for (int cntL = 0; cntL + cntR <= len; ++cntL) {
                remin(minSum[len][cntR+cntL], minSum[len-cntR][cntL] + minFrom[pos][cntR]);
                remin(minSum[len][cntL], minSum[len-cntR][cntL]);
            }
        }
    }
    ll answ = INF;
    for (int cnt = minCnt; cnt <= n; ++cnt) {
        answ = std::min(answ, minSum[n][cnt]);
    }
    return answ == INF ? -1 : answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m, k;
    while (std::cin >> n >> m >> k) {
        std::vector<Triple> triples(m);
        for (auto& it : triples) {
            std::cin >> it.lt >> it.rt >> it.cost;
            it.lt--, it.rt--;
        }
        std::cout << solve(n, triples, k) << std::endl;
    }
    return 0;
}