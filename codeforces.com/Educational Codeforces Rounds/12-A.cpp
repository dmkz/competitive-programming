/*
    Problem: 665A. Buses Between Cities
    
    Solution: implementation, segments intersection, O(MAX)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>

typedef long long ll;

int main() {    
    int d1, t1, d2, t2;
    scanf("%d %d %d %d", &d1, &t1, &d2, &t2);
    
    int h, m;
    scanf("%d:%d", &h, &m);
    m += h * 60;
    
    int s = 5 * 60, f = 23 * 60 + 59;
    
    int count = 0;
    for (int begin = s; begin <= f; begin += d2) {
        const int end = begin + t2;
        // Intersect (begin, end) with (m, m+t1)
        if (end <= m || begin >= m+t1) {
            continue;
        }
        ++count;
    }
    printf("%d", count);
    return 0;
}