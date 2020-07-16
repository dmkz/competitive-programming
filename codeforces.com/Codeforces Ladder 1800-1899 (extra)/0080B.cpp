/*
    Problem: 80B. Depression
    Solution: geometry, angle, O(1)
*/
#include <bits/stdc++.h>
int main() {
    int h, m; scanf("%d:%d", &h, &m);
    h = 60 * (h % 12) + m;
    printf("%0.9f %0.9f\n", h / (12.0 * 60) * 360, m / 60.0 * 360);
}