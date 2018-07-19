/*
    Problem: 616A. Comparing Two Long Integers
    
    Solution: implementation, strings, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string a, b; 
    std::cin >> a >> b;
    
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    
    while (a.size() < b.size()) a.push_back('0');
    while (b.size() < a.size()) b.push_back('0');
    
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    
    std::cout << (a < b ? '<' : a > b ? '>' : '=');
    
    return 0;
}