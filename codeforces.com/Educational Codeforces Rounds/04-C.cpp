/*
    Problem: 612C. Replace To Make Regular Bracket Sequence
    
    Solution: stack, math, expression parsing, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

inline bool is_opened(char c) {
    return c == '[' || c == '(' || c == '<' || c == '{';
}

inline bool is_closed(char c) {
    return c == '[' || c == '(' || c == '<' || c == '{';
}

inline bool one_type(char c1, char c2) {
    return (c1 == '[' && c2 == ']') || (c1 == '(' && c2 == ')') || (c1 == '<' && c2 == '>') || (c1 == '{' && c2 == '}');
}

int main() {
    std::vector<char> buf(1000*1000+1);
    scanf("%1000000s", &buf[0]);
    std::string s(&buf[0]);
    
    std::vector<char> stack;
    int answer = 0;
    for (auto it : s) {
        if (is_opened(it)) {
            stack.push_back(it);
        } else {
            if (stack.empty()) {
                std::cout << "Impossible" << std::endl;
                return 0;
            }
            auto c = stack.back();
            stack.pop_back();
            answer += !one_type(c, it);
        }
    }
    if (stack.empty()) {
        std::cout << answer << std::endl;
    } else {
        std::cout << "Impossible" << std::endl;
    }
    return 0;
}