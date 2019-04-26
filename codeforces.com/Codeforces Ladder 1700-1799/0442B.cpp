/*
    Problem: 442B. Andrey and Problem
    
    Solution: greedy, probability theory, sorting, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
typedef long double ld;
int main() {
    std::cout << std::fixed << std::setprecision(9);
    for (int n; std::cin >> n; ) {
        std::vector<ld> p(n);
        for (int i = 0; i < n; ++i) { std::cin >> p[i]; }
        std::sort(p.begin(),p.end(),std::greater<ld>());
        ld Q = 1, P = 0, answ = 0;
        for (auto it : p) {
            ld NQ = Q * (1 - it);
            ld NP = P * (1 - it) + Q * it;
            answ = std::max(answ, NP);
            Q = NQ;
            P = NP;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}