/*
    Problem: 220A. Little Elephant and Problem
    Solution: dynamic programming
*/
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    a.push_back((int)1e9+1);
    
    std::vector<int> imin(1+n);
    imin[n] = n;
    for (int i = n-1; i >= 0; --i) {
        int im = imin[i+1];
        imin[i] = a[i] < a[im] ? i : im;
    }
    int pos = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[i+1]) {
            for (pos = i; pos > 0 && a[pos-1] == a[i]; --pos);
            break;
        }
    }
    if (pos >= 0) {
        int pos2 = imin[pos+1];
        std::swap(a[pos], a[pos2]);
    }
    std::cout << (std::is_sorted(a.begin(), a.end()) ? "YES" : "NO");
    return 0;
}