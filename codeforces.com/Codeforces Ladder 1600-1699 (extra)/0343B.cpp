/*
    Problem: 343B. Alternating Current
    
    Solution: stack, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::string s;
    while (std::cin >> s) {
        std::vector<char> stack;
        for (auto it : s) {
            if (stack.empty()) {
                stack.push_back(it);
            } else if (stack.back() == it) {
                stack.pop_back();
            } else {
                stack.push_back(it);
            }
        }
        std::cout << (stack.empty() ? "Yes" : "No") << std::endl;
    }
    return 0;
}