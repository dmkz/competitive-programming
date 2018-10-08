/*
    Problem: 556A. Case of the Zeros and Ones
    
    Solution: greedy, stack, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    int n; std::string s;
    std::cin >> n >> s;
    
    std::vector<char> stack;
    for (auto& it : s) {
        if (!stack.empty() && stack.back() != it) {
            stack.pop_back();
        } else {
            stack.push_back(it);
        }
    }
    std::cout << stack.size();
    return 0;
}