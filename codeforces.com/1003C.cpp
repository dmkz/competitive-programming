/*
    Solution: Prefix sum, O(n^2)
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cassert>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, minLen; std::cin >> n >> minLen;
    
    std::vector<int> sum(1+n);
    for (int i = 1; i <= n; ++i) {
        int val; std::cin >> val;
        sum[i] = sum[i-1] + val;
    }
    
    double max = 0;
    for (int len = minLen; len <= n; ++len) {
        for (int pos = 0; pos+len-1 < n; ++pos) {
            max = std::max(max, 1.0*(sum[pos+len] - sum[pos]) / len);
        }
    }
    std::cout << std::fixed << std::setprecision(8) << max;
    
    return 0;
}