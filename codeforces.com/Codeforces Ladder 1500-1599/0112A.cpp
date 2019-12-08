/*
    Problem: 112A. Petya and Strings
    Solution: strings, implementation
*/
#include <iostream>
#include <string>

int main() {
    std::string s, t;
    std::cin >> s >> t;
    for (auto& it : s) it = 'A' <= it && it <= 'Z' ? it - 'A' + 'a' : it;
    for (auto& it : t) it = 'A' <= it && it <= 'Z' ? it - 'A' + 'a' : it;
    if (s < t) {
        std::cout << -1;
    } else if (s > t) {
        std::cout << 1;
    } else if (s == t) {
        std::cout << 0;
    }
    return 0;
}