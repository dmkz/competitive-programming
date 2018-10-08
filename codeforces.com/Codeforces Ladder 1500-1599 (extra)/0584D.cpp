/*
    Problem: 584D. Dima and Lisa
    
    Solution: greedy, math, number theory, primes, O(sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>
#include <vector>

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

void fast(int n, int& a, int& b, int &c) {
    a = n, b = 0, c = 0;
    while (a > 0) {
        while (a > 0 && !is_prime(a)) --a;
        b = n - a;
        if (b == 0) return;
        while (b > 0) {
            while (b > 0 && !is_prime(b)) --b;
            c = n - a - b;
            if (c == 0 || is_prime(c)) return;
            --b;
        }
        --a;
    }
}

int main() {
    int n, a, b, c;
    std::cin >> n;
    fast(n,a,b,c);
    assert(a+b+c == n);
    assert(a == 0 || is_prime(a));
    assert(b == 0 || is_prime(b));
    assert(c == 0 || is_prime(c));
    std::vector<int> answ;
    if (a != 0) answ.push_back(a);
    if (b != 0) answ.push_back(b);
    if (c != 0) answ.push_back(c);
    std::cout << answ.size() << "\n";
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}