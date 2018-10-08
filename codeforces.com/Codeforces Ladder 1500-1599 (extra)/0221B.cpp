/*
    Problem: 221B. Little Elephant and Numbers
    
    Solution: math, number theory, divisors, O(sqrt(n) log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

bool check(int d, int x) {
    std::vector<bool> is(10, false);
    do {
        is[x % 10] = 1;
        x /= 10;
    } while (x > 0);
    do {
        if (is[d % 10]) return true;
        d /= 10;
    } while (d > 0);
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int x; std::cin >> x;
    std::vector<int> div{1}, stack{x};
    for (int i = 2; i * i <= x; ++i) {
        int j = x / i;
        if (i * j == x) {
            div.push_back(i);
            stack.push_back(j);
        }
    }
    if (stack.back() == div.back()) stack.pop_back();
    while (!stack.empty()) {
        div.push_back(stack.back());
        stack.pop_back();
    }
    
    int answ = 0;
    for (auto d : div) {
        answ += check(d, x);
    }
    std::cout << answ;
    return 0;
}