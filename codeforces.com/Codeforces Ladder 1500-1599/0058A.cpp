/*
    Problem: 58A. Chat room
    Solution: greedy, strings, O(n)
*/

#include <iostream>
#include <string>

int main() {
    std::string t = "hello";
    std::string s;
    std::cin >> s;
    for (int i = 0, p = 0; i < (int)t.size(); ++i) {
        while (p < (int)s.size() && s[p] != t[i]) ++p;
        if (p == (int)s.size()) {
            std::cout << "NO";
            return 0;
        }
        ++p;
    }
    std::cout << "YES";
    return 0;
}