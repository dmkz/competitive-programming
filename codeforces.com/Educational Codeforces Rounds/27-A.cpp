/*
    Problem: 845A. Chess Tourney
    
    Solution: sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> a(2*n);
    for (auto& it : a) scanf("%d", &it);
    std::sort(a.begin(), a.end());
    printf(a[n-1] < a[n] ? "YES" : "NO");
    return 0;
}