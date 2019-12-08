/*
    Problem: 455A. Boredom
    Solution: dynamic programming
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    const int AMAX = 1e5;
    std::vector<int> cnt(1+AMAX);
    
    int n; std::cin >> n;
    while (n--) { int a; std::cin >> a; cnt[a]++; }
    
    std::vector<ll> max(1+AMAX);
    max[0] = 0; max[1] = cnt[1];
    for (int i = 2; i <= AMAX; ++i) {
        max[i] = std::max((ll)cnt[i] * i + max[i-2], max[i-1]);
    }
    std::cout << max[AMAX];
    
    return 0;
}