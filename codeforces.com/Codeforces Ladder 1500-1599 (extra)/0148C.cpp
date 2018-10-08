/*
    Problem: 148C. Terse princess
    
    Solution: constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <cassert>

bool check(std::vector<int> answ, int nOh, int nWow) {
    int sum = answ[0];
    for (int i = 1; i < (int)answ.size(); ++i) {
        if (answ[i] > sum) {
            nWow--;
        } else if (answ[i] > answ[i-1]) {
            nOh--;
        } else if (answ[i] > 50000 || answ[i] < 1) {
            return false;
        }
        sum += answ[i];
    }
    return nWow == 0 && nOh == 0;
}

int main() {
    int n, nOh, nWow; 
    scanf("%d %d %d", &n, &nOh, &nWow);
    int nOhSaved = nOh, nWowSaved = nWow;
    std::vector<int> answ(n, 1);
    int sum = 1;
    for (int i = 1; i < n; ++i) {
        if (i == 1 && nWow == 0) {
            answ[i] = 1;
        } else if (nWow > 0) {
            answ[i] = sum + 1;
            --nWow;
        } else if (nOh > 0) {
            answ[i] = answ[i-1] + 1;
            assert(answ[i] <= sum);
            --nOh;
        }
        sum += answ[i];
    }
    if (!check(answ, nOhSaved, nWowSaved)) {
        printf("-1"); return 0;
    }
    for (auto it : answ) {
        printf("%d ", it);
    }
    return 0;
}