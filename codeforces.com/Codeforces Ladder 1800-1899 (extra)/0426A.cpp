/*
    Problem: 426A. Sereja and Mugs
    Solution: implementation, O(n)
*/
#include <bits/stdc++.h>
int main() {
    int n, s, max(1); scanf("%d %d", &n, &s);
    for (int a; n--; s -= a, max = std::max(max, a)) scanf("%d", &a);
    std::cout << (s + max >= 0 ? "YES" : "NO") << std::endl;
}