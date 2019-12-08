/*
    Problem: 166A. Rank List
    Solution: sorting, two pointers
*/
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

struct Pair {
    int res, time;
};

inline bool operator<(const Pair& a, const Pair& b) {
    return a.res > b.res || (a.res == b.res && a.time < b.time);
}

inline bool operator==(const Pair& a, const Pair& b) {
    return a.res == b.res && a.time == b.time;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    --k;
    std::vector<Pair> pairs;
    for (int i = 0; i < n; ++i) {
        int r, t; std::cin >> r >> t;
        pairs.push_back(Pair{r,t});
    }
    std::sort(pairs.begin(), pairs.end());
    int l = k, r = k;
    while (l >= 0 && pairs[l] == pairs[k]) --l;
    while (r < n && pairs[r] == pairs[k]) ++r;
    std::cout << r - l - 1;
    return 0;
}