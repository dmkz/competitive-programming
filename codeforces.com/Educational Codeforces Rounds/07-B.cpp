/*
    Problem: 622B. The Time
    
    Solution: math, implementation, O(1)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>

int main() {
    int h, m;
    scanf("%d:%d", &h, &m);
    m += 60 * h;
    int a; scanf("%d", &a);
    m += a;
    printf("%02d:%02d\n", m / 60 % 24, m % 60);
    return 0;
}