/*
    Problem: 416A. Guess a number!
    
    Solution: implementation, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>

typedef long long ll;

int main() {
    int n; std::cin >> n;
    ll low = -(ll)2e9, high = (ll)2e9;
    while (n--) {
        std::string op, answ; ll x;
        std::cin >> op >> x >> answ;
        if (op == ">=") {
            if (answ == "Y") {
                low = std::max(low, x);
            } else {
                high = std::min(high, x-1);
            }
        } else if (op == ">") {
            if (answ == "Y") {
                low = std::max(low, x+1);
            } else {
                high = std::min(high, x);
            }
        } else if (op == "<=") {
            if (answ == "Y") {
                high = std::min(high, x);
            } else {
                low = std::max(low, x+1);
            }
        } else if (op == "<") {
            if (answ == "Y") {
                high = std::min(high, x-1);
            } else {
                low = std::max(low, x);
            }
        } else {
            assert(false);
        }
    }
    if (low > high) {std::cout << "Impossible"; return 0;}
    std::cout << low;
    return 0;
}