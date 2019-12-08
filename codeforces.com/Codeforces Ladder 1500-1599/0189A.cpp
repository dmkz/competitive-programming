/*
    Problem: 189A. Cut Ribbon
    Solution: brute force
*/
#include <iostream>
#include <algorithm>

int main() {
    int n, a, b, c;
    std::cin >> n >> a >> b >> c;
    int answ = 0;
    for (int na = 0; na <= n / a; ++na) {
        for (int nb = 0; nb <= (n - na * a) / b; ++nb) {
            int rem = n - na * a - nb * b;
            if (rem % c != 0) continue;
            int nc = rem / c;
            answ = std::max(answ, na+nb+nc);
        }
    }
    std::cout << answ;
    return 0;
}