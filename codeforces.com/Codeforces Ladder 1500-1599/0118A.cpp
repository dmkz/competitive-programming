/*
    Problem: 118A. String Task
    Solution: implementation, strings
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    std::vector<char> to_erase = {'A', 'O', 'Y', 'E', 'U', 'I'};
    for (auto& it : to_erase) {
        it = it - 'A' + 'a';
    }
    std::string s;
    std::cin >> s;
    std::string t = "";
    for (auto& it : s) {
        it = 'A' <= it && it <= 'Z' ? it - 'A' + 'a' : it;
        if (std::find(to_erase.begin(), to_erase.end(), it) == to_erase.end()) {
            t.push_back('.');
            t.push_back(it);
        }
    }
    std::cout << t;
    return 0;
}