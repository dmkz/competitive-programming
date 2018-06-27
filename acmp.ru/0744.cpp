/*
    "Скобочки-3": циклические сдвиги, стек, правильная скобочная последовательность
*/

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

inline bool is_open(char c) {
    return c == '(' || c == '[' || c == '{';
}

inline bool same_type(char c1, char c2) {
    return 
        (c1 == '(' && c2 == ')') ||
        (c1 == '[' && c2 == ']') ||
        (c1 == '{' && c2 == '}');
}

bool correct(const std::string& s) {
    std::vector<char> stack;
    for (auto c : s) {
        if (is_open(c)) {
            stack.push_back(c);
        } else {
            if (stack.empty() || !same_type(stack.back(), c)) {
                return false;
            }
            stack.pop_back();
        }
    }
    return stack.empty();
}

int main() {
    char buf[1001] = {}; 
    scanf("%1000s", buf);
    std::string s(buf);
    for (int i = 0; i < (int)s.size(); ++i) {
        std::rotate(s.begin(), s.begin()+1, s.end());
        if (correct(s)) {
            printf("YES");
            return 0;
        }
    }
    printf(s.empty() ? "YES" : "NO");
    return 0;
}