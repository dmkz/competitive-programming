/*
    Problem: 414B. Mashmokh and ACM
    Solution: combinatorics, dynamic programming, number theory
*/
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> divisors(int n) {
    std::vector<int> answer{1}, stack{n};
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            answer.push_back(i);
            stack.push_back(n / i);
        }
    }
    if (stack.back() == answer.back()) {
        stack.pop_back();
    }
    while (!stack.empty()) { 
        answer.push_back(stack.back()); 
        stack.pop_back(); 
    }
    return answer;
}

const int MOD = (int)1e9+7;

int add(int a, int b) {
    return (a+=b) >= MOD ? a - MOD : a;
}

int main() {
    int n, steps;
    std::cin >> n >> steps;
    std::vector<int> curr(1+n), prev(1+n);
    for (int i = 1; i <= n; ++i) {
        curr[i] = 1;
    }
    
    std::vector<std::vector<int>> div(1+n);
    for (int i = 1; i <= n; ++i) {
        div[i] = divisors(i);
    }
    
    while (steps > 1) {
        for (int i = 1; i <= n; ++i) {
            for (auto& d : div[i]) {
                prev[d] = add(prev[d], curr[i]);
            }
        }
        curr.swap(prev);
        std::fill(prev.begin(), prev.end(), 0);
        --steps;
    }
    int answ = 0;
    for (auto& it : curr) {
        answ = add(answ, it);
    }
    std::cout << answ;
    return 0;
}