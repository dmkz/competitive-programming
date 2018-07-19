/*
    Problem: 609A. USB Flash Drives
    
    Solution: sorting, greedy, implementation, O(n log(n)+m)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef int64_t Int;

int main() {    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    Int n, m; std::cin >> n >> m;
    
    std::vector<Int> a(n); for (auto& it : a) std::cin >> it;
    
    std::sort(a.begin(), a.end());
    
    Int answer = 0;
    while (m > 0) {
        m -= a.back();
        a.pop_back();
        ++answer;
    }
    std::cout << answer;   
    
    return 0;
}