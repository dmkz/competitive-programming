/*
    Problem: 424C. Magic Formulas
    
    Solution: number theory, math, prefix sums, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
int main() {
    int n, q = 0; scanf("%d", &n);
    for (int i = 0, p; i < n; ++i) {
        scanf("%d", &p);
        q ^= p;
    }
    std::vector<int> pref(1+n);
    for (int i = 1; i <= n; ++i) {
        pref[i] = i ^ pref[i-1];
    }
    for (int mod = 1; mod <= n; ++mod) {
        int k = (n / mod) % 2;
        q ^= pref[n % mod];
        if (k == 1) {q ^= pref[mod-1];}
    }
    printf("%d", q);
    return 0;
}