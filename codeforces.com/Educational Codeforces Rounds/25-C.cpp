/*
    Problem: 825C. Multi-judge Solving
    
    Solution: greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <queue>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;

int main() {
    int n, max, answ = 0;
    scanf("%d %d", &n, &max);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < n; ++i) {
        if (2*max >= arr[i]) {
            max = std::max(max, arr[i]);
        } else {
            ++answ;
            max *= 2;
            --i;
        }
    }
    printf("%d", answ);
    return 0;
}