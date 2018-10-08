/*
    Problem: 369B. Valera and Contest
    
    Solution: constructive, greedy, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>

int main() {
    int n2, n1, a, b, s2, s1;
    scanf("%d %d %d %d %d %d", &n2, &n1, &a, &b, &s2, &s1);
    s2 -= s1, n2 -= n1;
    if (n2 == 0) {
        std::vector<int> fi(n1);
        int p = 0;
        while (s1 > 0) {
            fi[p]++;
            p++;
            s1--;
            if (p == n1) p = 0;
        }
        for (auto& it : fi) printf("%d ", it);
        return 0;
    }
    for (int i = a; i <= b; ++i) {
        for (int j = a; j <= i; ++j) {
            // i * (n1-1) <= s1 - i <= b * (n1-1)
            // a * (n2-1) <= s2 - j <= j * (n2-1)
            if (s1 - i < i * (n1-1)) continue;
            if (s1 - i > b * (n1-1)) continue;
            if (s2 - j < a * (n2-1)) continue;
            if (s2 - j > j * (n2-1)) continue;
            std::vector<int> fi(n1, i), se(n2, a);
            se[0] = j;
            s1 -= n1 * i;
            s2 -= j + (n2-1) * a;
            int p = 0;
            while (s1 > 0) {
                fi[p]++;
                s1--;
                p++;
                if (p == n1-1) {
                    p = 0;
                }
            }
            p = 1;
            while (s2 > 0) {
                se[p]++;
                s2--;
                p++;
                if (p == n2) p = 1;
            }
            for (auto& it : fi) printf("%d ", it);
            for (auto& it : se) printf("%d ", it);
            return 0;
        }
    }
    throw 1;
}