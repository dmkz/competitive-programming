/*
    Problem: 818B. Permutation Game
    
    Solution: implementation, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    std::vector<int> a(1+n);
    int prev; scanf("%d", &prev);
    for (int i = 1; i < m; ++i) {
        int curr; scanf("%d", &curr);
        int diff = curr - prev;
        if (diff <= 0) diff += n;
        if (a[prev] == 0 || a[prev] == diff) {
            a[prev] = diff;
            prev = curr;
        } else {
            printf("-1"); return 0;
        }
    }
    std::vector<int> cnt(1+n);
    for (auto it : a) {
        cnt[it]++;
        if (it != 0 && cnt[it] > 1) { printf("-1"); return 0; }
    }
    int pos = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) {
            while (cnt[pos] > 0)++pos;
            a[i] = pos;
            cnt[pos]++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
    }
    return 0;
}