/*
    Problem: 122B. Lucky Substring
    
    Solution: greedy, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int n4 = 0, n7 = 0; std::string s; std::cin >> s;
    for (auto it : s) {
        n4 += (it == '4');
        n7 += (it == '7');
    }
    if (!n4 && !n7) { std::cout << -1; return 0; }
    std::cout << (n4 >= n7 ? "4" : "7");
    return 0;
}