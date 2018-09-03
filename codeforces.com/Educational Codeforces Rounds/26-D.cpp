/*
    Problem: 837D. Round Subset
    
    Solution: dynamic programming, O(n^2*k*log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize ("O3")
#include <cstdio>
#include <algorithm>
#include <vector>

#define remax(x,y) if ((y) > (x)) (x) = (y)

typedef long long ll;

struct Pair {
    int n2, n5;
    
    Pair (ll number) {
        n2 = 0, n5 = 0;
        while (number % 2 == 0) {
            number /= 2; n2++;
        }
        while (number % 5 == 0) {
            number /= 5; n5++;
        }
    }
};

const int INF = (int)1e9+1;

int main() {
    int n, need;
    scanf("%d %d", &n, &need);
    std::vector<std::vector<int>> curr(1+need,std::vector<int>(201*26, -INF));
    auto prev = curr;
    curr[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        ll number; scanf("%lld", &number);
        Pair state(number);
        prev = curr;
        for (int k = 1; k <= need; ++k) {
            for (int n5 = state.n5; n5 < 201*26; ++n5) {
                remax(curr[k][n5],prev[k-1][n5-state.n5] + state.n2);
            }
        }
    }
    int answ = 0;
    for (int n5 = 0; n5 < 201*26; ++n5) {
        answ = std::max(answ, std::min(curr[need][n5], n5));
    }
    printf("%d", answ);
    return 0;
}