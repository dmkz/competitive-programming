/*
    Problem: 495B. Modular Equations
    
    Solution: number theory, math, divisors, O(sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

typedef std::vector<int> vi;

const int INF = (int)1e9+1;

vi divisors(int n) {
    vi answ{1}, stack{n};
    for (int i = 2; i * i <= n; ++i) {
        int j = n / i;
        if (j * i == n) {
            answ.push_back(i);
            stack.push_back(j);
        }
    }
    if (answ.back() == stack.back()) {
        stack.pop_back();
    }
    while (!stack.empty()) {
        answ.push_back(stack.back());
        stack.pop_back();
    }
    return answ;
}

int solve(int a, int b) {
    if (b > a) return 0;
    if (a == b) return INF;
    int answ = 0;
    for (auto it : divisors(a-b)) {
        answ += (a % it == b);
    }
    return answ;
}

int main() {
    int a, b;
    while (std::cin >> a >> b) {
        int answ = solve(a, b);
        if (answ == INF) {
            std::cout << "infinity" << std::endl;
        } else {
            std::cout << answ << std::endl;
        }
    }
    return 0;
}