/*
    Problem: 604B. More Cowbell
    
    Solution: binary search, greedy, O(n * log(s))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>

bool can(std::vector<int> arr, int k, int s) {
    int n = (int)arr.size(), i = 0, j = n-1;
    while (i <= j && k > 0) {
        if (i == j) {
            if (arr[i] > s) return false;
            ++i;
        } else if (arr[i] + arr[j] > s) {
            if (arr[j] > s) return false;
            --j;
        } else {
            ++i, --j;
        }
        --k;
    }
    return i > j;
}


int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    if (n == 1) {printf("%d\n", arr[0]); return 0;}
    int low = 0, high = (int)1e9;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (can(arr, k, mid)) {
            high = mid;
        } else low = mid;
    }
    printf("%d", high);
    return 0;
}