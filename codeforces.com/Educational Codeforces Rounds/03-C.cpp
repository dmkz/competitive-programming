/*
    Problem: 609C. Load Balancing
    
    Solution: sorting by counting, greedy, implementation, O(n+m)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef int64_t Int;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    Int nServ; std::cin >> nServ;
    
    std::vector<Int> count(1+2*10000, 0);
    
    for (Int i = 0; i < nServ; ++i) {
        Int c; std::cin >> c;
        count[c]++;
    }
    
    Int l = 0, r = 2*10000, answer = 0;
    while (true) {
        while (l <= 2*10000 && count[l] == 0) ++l;
        while (r >= l && count[r] == 0) --r;
        if (r - l < 2) {std::cout << answer; return 0; }
        Int d = std::min(count[l], count[r]);
        count[l] -= d;
        count[l+1] += d;
        count[r] -= d;
        count[r-1] += d;
        answer += d;
    }
    std::cout << answer;
    
    return 0;
}