/*
    Problem: 51C. Three Base Stations
    
    Solution: binary search, sorting, greedy, O(n log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
typedef double Real;
int main() {    
    int n; scanf("%d", &n);
    std::vector<int> x(n);
    for (auto& it : x) scanf("%d", &it);
    std::sort(x.begin(), x.end());
    std::function<bool(Real,Real&,Real&,Real&)> can = [&](Real d, Real& p1, Real& p2, Real& p3) {
        p1 = x[0] + d;
        int i = 0;
        while (i < n && x[i] <= p1 + d) ++i;
        if (i == n) {p2 = p3 = p1; return true;}
        p2 = x[i] + d;
        while (i < n && x[i] <= p2 + d) ++i;
        if (i == n) {p3 = p2; return true;}
        p3 = x[i] + d;
        while (i < n && x[i] <= p3 + d) ++i;
        if (i == n) {return true;}
        return false;
    };
    Real low = 0, high = 1e9+1;
    std::vector<Real> answ;
    for (int i = 0; i < 64; ++i) {
        Real mid = (low + high) / 2, p1, p2, p3;
        if (can(mid,p1,p2,p3)) {
            high = mid;
            answ = {p1,p2,p3};
        } else low = mid;
    }
    printf("%0.6f\n", high);
    for (auto it : answ) printf("%0.6f ", it);
    return 0;
}