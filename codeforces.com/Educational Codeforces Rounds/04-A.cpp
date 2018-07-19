/*
    Problem: 612A. The Text Splitting
    
    Solution: brute force, implementation, strings, O(n^2)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::pair<int, int> solve(std::string s, int x, int y) {
// a*x+b*y = n
    const int n = (int)s.size();
    for (int a = 0; a * x <= n; ++a)
        for (int b = 0; a*x + b*y <= n; ++b)
            if (a * x + b * y == n)
                return {a, b};
    return {-1, -1};
}

int main() {
    int n, x, y; 
    std::cin >> n >> x >> y;
    std::string s; 
    std::cin >> s;
    // a*x+b*y = n
    auto p = solve(s, x, y);
    if (p.first == -1) {
        std::cout << "-1" << std::endl; return 0;
    }
    std::vector<std::string> answ;
    while (p.first > 0) {
        answ.push_back(s.substr((int)s.size()-x, x));
        for (int i = 0; i < x; ++i)
            s.pop_back();
        p.first--;
    }
    while (p.second > 0) {
        answ.push_back(s.substr((int)s.size()-y, y));
        for (int i = 0; i < y; ++i)
            s.pop_back();
        p.second--;
    }
    std::reverse(answ.begin(), answ.end());
    std::cout << answ.size() << std::endl;
    for (auto & s : answ) std::cout << s << std::endl;
    
    return 0;
}