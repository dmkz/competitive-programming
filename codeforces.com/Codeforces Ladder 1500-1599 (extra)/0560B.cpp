/*
    Problem: 560B. Gerald is into Art
    
    Solution: geometry, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>

bool can(int W, int H, int w1, int h1, int w2, int h2) {
    if (w1 > W || h1 > H || w2 > W || h2 > H) return false;
    return !(W-w2 < w1 && H-h2 < h1);
}


int main() {
    int W, H, w1, h1, w2, h2;
    scanf("%d %d %d %d %d %d", &W, &H, &w1, &h1, &w2, &h2);
    if (W < H) std::swap(W,H);
    if (
        can(W, H, w1, h1, w2, h2) || 
        can(W, H, h1, w1, w2, h2) ||
        can(W, H, w1, h1, h2, w2) ||
        can(W, H, h1, w1, h2, w2)
    ) {
        printf("YES");
    } else printf("NO");
    return 0;
}