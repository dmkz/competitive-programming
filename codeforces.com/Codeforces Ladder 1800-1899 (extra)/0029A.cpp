/*
    Problem: 29A. Spit Problem
    Solution: std::set, searching, pairs, O(n log(n))
*/
#include <bits/stdc++.h>
using pii = std::pair<int,int>;
int main() {
    int n; scanf("%d", &n);
    std::set<pii> s;
    while (n--) {
        int p,d; scanf("%d %d", &p, &d);
        s.insert({p,p+d});
    }
    bool ok = false;
    for (auto [x,y] : s) ok |= s.count({y,x});
    printf(ok ? "YES\n" : "NO\n");
}