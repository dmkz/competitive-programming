/*
    Problem: 385A. Bear and Raspberry
    Solution: brute force, implementation, O(n)
*/
#include <bits/stdc++.h>
int main() {
    int n, c; scanf("%d %d", &n, &c);
    int answ(0);
    std::vector<int> d(n);
    for (auto &it : d) {
        scanf("%d", &it);
    }
    for (int i = 1; i < n; i++) {
        if (d[i] <= d[i-1]) {
            answ = std::max(answ,d[i-1]-d[i]-c);
        }
    }
    printf("%d\n", answ);
}