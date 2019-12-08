/*
    Problem: 264A. Escape from Stones
    Solution: constructive, std::stack
*/
#include <iostream>
#include <string>
#include <stack>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s; s = "?" + s;
    std::stack<int> stack;
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i] == 'l') {
            stack.push(i);
        } else {
            std::cout << i << '\n';
        }
    }
    while (!stack.empty()) {
        std::cout << stack.top() << '\n';
        stack.pop();
    }
    return 0;
}