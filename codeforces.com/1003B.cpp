/*
    Solution: Strings, Constructive, O(n)
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n0, n1, x;
    std::cin >> n0 >> n1 >> x;
    std::string s = n1 > n0 ? "1" : "0";
    while (x--) {
        s.push_back('1' - s.back() + '0');
    }
    
    for (auto& it : s) {
        n0 -= (it == '0');
        n1 -= (it == '1');
    }
    assert(n0 >= 0 && n1 >= 0);
    
    int p1 = s.find('1');
    
    s = s.substr(0, p1) + std::string(n1, '1') + s.substr(p1);
    
    int p0 = s.find('0');
    
    s = s.substr(0, p0) + std::string(n0, '0') + s.substr(p0);
    
    std::cout << s;
    
    return 0;
}