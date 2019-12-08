/*
    Problem: 279C. Ladder
    Solution: dynamic programming, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for(auto& it : a) std::cin >> it;
    
    std::vector<int> pref(n, 1), suff(n, 1);
    for (int i = n-2; i >= 0; --i) {
        pref[i] = a[i] <= a[i+1] ? pref[i+1] + 1 : 1;
    }
    for (int i = 1; i < n; ++i) {
        suff[i] = a[i] <= a[i-1] ? suff[i-1] + 1 : 1;
    }
    while (q--) {
        int l, r; std::cin >> l >> r; --l, --r;
        std::cout << (pref[l] + suff[r] < r - l + 1 ? "No" : "Yes") << '\n';
    }
    
    return 0;
}