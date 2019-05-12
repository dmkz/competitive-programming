/*
    Problem: 546D. Soldier and Number Game
    
    Solution: sieve, dynamic programming, number theory, math, O(n+t)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
namespace Solution {
    const int XMAX = 5*1000*1000+1;
    int primeDiv[XMAX], sumPow[XMAX], sumFact[XMAX];
    void init() {
        for (int i = 2; i * i < XMAX; ++i) {
            if (primeDiv[i] != 0) { continue; }
            for (int j = i * i; j < XMAX; j += i) {
                primeDiv[j] = i;
            }
        }
        for (int i = 2; i < XMAX; ++i) {
            if (primeDiv[i] == 0) {
                primeDiv[i] = i;
            }
            sumPow[i] = sumPow[i / primeDiv[i]] + 1;
            sumFact[i] = sumFact[i-1] + sumPow[i];
        }
    }
    int solve(int a) {
        return sumFact[a];
    }
}
int main() {
    using namespace Solution;
    init();
    int nT; scanf("%d", &nT);
    while (nT--) {
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", solve(a) - solve(b));
    }
    return 0;
}