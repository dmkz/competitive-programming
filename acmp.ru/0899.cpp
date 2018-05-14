#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

bool is_opened(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool is_one_type(char c1, char c2) {
    return (c1 == '(' && c2 == ')') || (c1 == '{' && c2 == '}') || (c1 == '[' && c2 == ']');
}

int solve(const std::string& s) {
    std::stack<char> stack;
    for (auto& it : s) {
        if (is_opened(it)) {
            stack.push(it);
        } else {
            if (stack.empty()) return 1;
            char c = stack.top(); stack.pop();
            if (!is_one_type(c, it)) {
                return 1;
            }
        }
    }
    return stack.empty() ? 0 : 1;
}

int main() {
    for (std::string s; std::cin >> s; std::cout << solve(s));    
    return 0;
}