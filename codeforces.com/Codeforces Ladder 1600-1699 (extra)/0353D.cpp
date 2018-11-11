/*
    Problem: 353D. Queue
    
    Solution: stack, implementation, constructive, queries offline, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

struct Block {
    int last, len, add;
};

int solve(std::string s) {
    while (!s.empty() && s.back() == 'M') {
        s.pop_back();
    }
    std::vector<int> add;
    std::vector<Block> stack;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == 'M') {
            if (stack.empty() || stack.back().last != i-1) {
                stack.push_back(Block{i-1, 0, 0});
            }
            if (stack.back().last == i-1) {
                stack.back().last = i;
                stack.back().len++;
            }
        } else if (s[i] == 'F' && !stack.empty()) {
            stack.back().add++;
        }
    }
    for (int i = (int)stack.size()-2; i >= 0; --i) {
        stack[i].add += stack[i+1].add;
    }
    int answ = 0;
    while (!stack.empty()) {
        auto back = stack.back();
        stack.pop_back();
        answ = std::max(answ, back.add + back.len - 1);
        if (!stack.empty()) {
            stack.back().add = std::max(stack.back().add, back.add + back.len);
        }
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}