/*
    Problem: 837C. Two Seals
    
    Solution: implementation, geometry, brute force, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

#define remax(x, y) if ((y) > (x)) (x) = (y)

struct Pair {
    
    int x, y; 
    
    int s() const {
        return x * y;
    }
};

int main() {
    int n, a, b; scanf("%d %d %d", &n, &a, &b);
    std::vector<Pair> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
    }
    int answ = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            {
                int right = arr[i].x;
                int bottom = arr[i].y;
                int left = b - arr[j].x;
                int top = a - arr[j].y;
                if (!(right > b || left < 0 || top < 0 || bottom > a)) {
                    if (right <= left || bottom <= top) {
                        remax(answ, arr[i].s()+arr[j].s());
                    }
                }
            }
            {
                int right = arr[i].y;
                int bottom = arr[i].x;
                int top = a - arr[j].y;
                int left = b - arr[j].x;
                if (!(right > b || left < 0 || top < 0 || bottom > a)) {
                    if (right <= left || bottom <= top) {
                        remax(answ, arr[i].s()+arr[j].s());
                    }
                }
            }
            {
                int right = arr[i].x;
                int bottom = arr[i].y;
                int top = a - arr[j].x;
                int left = b - arr[j].y;
                if (!(right > b || left < 0 || top < 0 || bottom > a)) {
                    if (right <= left || bottom <= top) {
                        remax(answ, arr[i].s()+arr[j].s());
                    }
                }
            }
            {
                int right = arr[i].y;
                int bottom = arr[i].x;
                int top = a - arr[j].x;
                int left = b - arr[j].y;
                if (!(right > b || left < 0 || top < 0 || bottom > a)) {
                    if (right <= left || bottom <= top) {
                        remax(answ, arr[i].s()+arr[j].s());
                    }
                }
            }
        }
    }
    printf("%d", answ);
    return 0;
}