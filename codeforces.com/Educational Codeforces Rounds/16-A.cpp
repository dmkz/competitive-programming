/*
    Problem: 710A. King Moves
    
    Solution: math, implementation, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    char c, r;
    scanf(" %c %c", &c, &r);
    c -= 'a';
    r -= '1';
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr*dr+dc*dc == 0)continue;
            int nr = r + dr;
            int nc = c + dc;
            count += !(nr < 0 || nr > 7 || nc < 0 || nc > 7);
        }
    }
    printf("%d", count);
    return 0;
}