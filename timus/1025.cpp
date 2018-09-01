/*
    Problem: 1025. Democracy in Danger
    
    Solution: sorting, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> a(n);
    for (auto& it : a) scanf("%d", &it);
    std::sort(a.begin(), a.end());
    int answ = 0;
    for (int i = 0; i <= n / 2; ++i) {
        answ += (a[i]+1)/2;
    }
    printf("%d", answ);
    return 0;
}