/*
    Problem: 617C. Watering Flowers
    
    Solution: geometry, sorting, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

ll dist2(int x1, int y1, int x2, int y2) {
    int dx = x1-x2,dy = y1-y2;
    return (ll)dx*dx+(ll)dy*dy;
}

int main() {
    int n, x1, y1, x2, y2;
    scanf("%d %d %d %d %d", &n, &x1, &y1, &x2, &y2);
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }
    std::vector<int> v1, v2, pos2(n);
    for (int i = 0; i < n; ++i) {
        v1.push_back(i); v2.push_back(i);
    }
    std::stable_sort(v1.begin(), v1.end(), [&](int i, int j) {
        return dist2(x1, y1, x[i], y[i]) < dist2(x1, y1, x[j], y[j]);
    });
    std::stable_sort(v2.begin(), v2.end(), [&](int i, int j) {
        return dist2(x2, y2, x[i], y[i]) < dist2(x2, y2, x[j], y[j]);
    });
    for (int i = 0; i < n; ++i) pos2[v2[i]] = i;
    
    std::vector<bool> in1(n, true), in2(n);
    int p1 = n-1, p2 = 0;
    ll best = std::min(
        dist2(x1,y1,x[v1.back()],y[v1.back()]),
        dist2(x2,y2,x[v2.back()],y[v2.back()])
    );
    while (p1 > 0) {
        p2 = std::max(p2, pos2[v1[p1]]);
        --p1;
        best = std::min(best, dist2(x1,y1,x[v1[p1]],y[v1[p1]])+dist2(x2,y2,x[v2[p2]],y[v2[p2]]));
    }
    std::cout << best;
    return 0;
}