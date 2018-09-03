/*
    Problem: 845D. Driving Test
    
    Solution: greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> limits{301};
    int nOver = 0, answ = 0, speed = 0;
    for (int i = 0; i < n; ++i) {
        int t; scanf("%d", &t);
        if (t == 1) {
            scanf("%d", &speed);
            while (!limits.empty() && speed > limits.back()) {
                limits.pop_back();
                answ++;
            }
        } else if (t == 2) {
            answ += nOver;
            nOver = 0;
        } else if (t == 3) {
            int lim; scanf("%d", &lim);
            if (speed > lim) {
                answ++;
            } else {
                limits.push_back(lim);
            }
        } else if (t == 4) {
            nOver = 0;
        } else if (t == 5) {
            limits.clear();
            limits.push_back(301);
        } else if (t == 6) {
            nOver++;
        }
    }
    printf("%d", answ);
    return 0;
}