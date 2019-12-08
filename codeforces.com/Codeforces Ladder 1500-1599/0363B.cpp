/*
    Problem: 363B. Fence
    Solution: dynamic programming, two pointers, brute force
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, len;
    std::cin >> n >> len;
    
    std::vector<int> h(n);
    for (auto& it : h) std::cin >> it;
    
    int sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += h[i];
    }
    
    std::vector<int> s(n-len+1);
    s[0] = sum;
    
    for (int i = 1; i+len-1 < n; ++i) {
        s[i] = s[i-1] - h[i-1] + h[i+len-1];
    }
    
    std::cout << int(std::min_element(s.begin(), s.end()) - s.begin()) + 1;
    
    return 0;
}