/*
    Problem: 357A. Group of Students
    Solution: brute force, implementation, O(n)
*/
#include <bits/stdc++.h>
int main() {
    int m,s(0); scanf("%d", &m);
    std::vector<int> c(1+m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &c[i]);
        s += c[i];
    }
    int x, y, answ(0); scanf("%d %d", &x, &y);
    for (int i = 1, p(0); i <= m; i++) {
        if (x <= p && p <= y && x <= s && s <= y) {
            answ = i;
        }
        p += c[i];
        s -= c[i];
    }
    printf("%d\n", answ);
}