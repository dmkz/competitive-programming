#include <bits/stdc++.h>

int solve(int k, const std::vector<int>& a) {
    int n = (int)a.size();
    assert(0 <= k && k <= n);
    
    if (k == 0) {
        return a[0] == 1 ? -1 : a[0]-1;
    }
    
    for (auto& it : a) {
        int count = int(std::upper_bound(a.begin(), a.end(), it) - a.begin());
        if (count == k) return it;
    }
    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
    
    int n, k; std::cin >> n >> k;
    
    if (n < k) {
        std::cout << "-1" << std::endl;
        return 0;
    }
    
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    
    std::sort(a.begin(), a.end());
    
    std::cout << solve(k, a) << std::endl;
    
    
    return 0;
}