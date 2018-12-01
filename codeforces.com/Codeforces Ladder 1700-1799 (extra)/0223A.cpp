/*
    Problem: 223A. Bracket Sequence
    
    Solution: stack, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct Triple {
    int lt, rt, cnt;
};

Triple solve(std::string s) {
    const int n = (int)s.size();
    s = "?" + s;
    std::vector<int> stack, cnt(1+n), leftPos(1+n, n+1);
    for (int i = 1; i <= n; ++i) {
        cnt[i] = cnt[i-1] + (s[i] == '[');
    }
    int max = 0, lt = 1, rt = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '(' || s[i] == '[') {
            stack.push_back(i);
        } else if (stack.empty() || 
            (s[stack.back()] == '(' && s[i] == ']') ||
            (s[stack.back()] == '[' && s[i] == ')')) 
        {
            stack.clear();            
        } else {
            int back = stack.back(); stack.pop_back();
            int right = i;
            int left = leftPos[right] = std::min(back, leftPos[back-1]);
            int curr = cnt[right]-cnt[left-1];
            if (curr > max) {
                max = curr, lt = left, rt = right;
            }
        }
    }
    return Triple{lt-1,rt-1,max};
}

int main() {
    std::string s;
    while (std::cin >> s) {
        auto answ = solve(s);
        std::cout << answ.cnt << '\n' << s.substr(answ.lt, answ.rt-answ.lt+1) << std::endl;
    }
    return 0;
}