/*
    Problem: 360B. Levko and Array
    Solution: binary search, dynamic programming, O(log(A) * n^2)
*/

#include <bits/stdc++.h>

template<class X, class Y> X& remin(X& x, Y y) {
    return x = (y < x ? y : x);
}

const int NMAX = 2020, INF = (int)1e9;

int n, k, arr[NMAX], minK[NMAX][NMAX]; // minK[prefix][lastKeeped]

bool check(int x) {
// check if we can get max difference less or equal `x`
    std::fill(&minK[0][0], &minK[0][0]+NMAX*NMAX, INF);
    minK[1][1] = 0;
    for (int prefix = 2; prefix <= n; prefix++) {
        // change last item:
        for (int last = 0; last <= prefix; last++) {
            remin(minK[prefix][last], minK[prefix-1][last] + 1);
        }
        // keep last item:
        const int last = prefix;
        remin(minK[prefix][last], prefix - 1); // remove all but keep last
        for (int prev = 1; prev < prefix; prev++) { // brute last keeped item
            if (std::abs(arr[last] - arr[prev]) <= (last - prev + 0LL) * x) {
                remin(minK[prefix][last], minK[prefix-1][prev]);
            }
        }
    }
    // check:
    return *std::min_element(minK[n] + 1, minK[n] + n + 1) <= k;
}

int solve() {
    int low = -1, high = (int)2e9;
    while (high - low > 1) {
        int mid = low + (high - low) / 2;
        if (check(mid)) { high = mid; }
        else { low = mid; }
    }
    return high;
}

int main() {
    while (std::cin >> n >> k) {
        for (int i = 1; i <= n; i++) std::cin >> arr[i];
        std::cout << solve() << std::endl;
    }
    return 0;
}