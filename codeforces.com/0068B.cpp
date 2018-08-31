/*
    Problem: 68B. Energy exchange
    
    Solution: binary search, sorting, O(n log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>

typedef double Real;

bool can(std::vector<Real> a, Real value, Real coeff) {
    if (a.back() >= value) return true;
    if (a.front() < value) return false;
    int l = 0, r = (int)a.size()-1;
    while (l <= r) {
        if (a[l] > value) {
            Real diff = (a[l] - value) * (100-coeff) / 100;
            a[l] = value;
            while (diff > 0 && r > l) {
                auto delta = std::min(value-a[r], diff);
                a[r] += delta;
                diff -= delta;
                if (diff > 0) {
                    --r;
                }
            }
        }
        if (a[l] < value) return false;
        ++l;
    }
    for (auto it : a) {
        if (it < value) return false;
    }
    return true;
}

int main() {
    int n; Real k;
    scanf("%d %lf", &n, &k);
    std::vector<Real> a(n);
    for (auto& it : a) {
        scanf("%lf", &it);
    }
    std::sort(a.begin(), a.end(), std::greater<Real>());
    Real low = 0, high = 1001;
    for (int i = 0; i < 64; ++i) {
        Real mid = (low + high) / 2;
        if (can(a, mid, k)) {
            low = mid;
        } else high = mid;
    }
    printf("%0.6f", low);
    return 0;
}