/*
    Problem: 580B. Kefa and Company
    
    Solution: sorting, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long ll;

struct Pair {
    int value, cost;
};

int main() {
    int n, limit;
    scanf("%d %d", &n, &limit);
    std::vector<Pair> arr(n);
    for (auto& it : arr) {
        scanf("%d %d", &it.value, &it.cost);
    }
    std::sort(arr.begin(), arr.end(), [](const Pair& a, const Pair& b) {
        return a.value < b.value || (a.value == b.value && a.cost < b.cost);
    });
    int l = 0, r = -1; ll answ = 0, curr = 0;
    while (l < n) {
        while (r+1 < n && arr[r+1].value - arr[l].value < limit) {
            curr += arr[++r].cost;
        }
        assert(l <= r && arr[r].value - arr[l].value < limit);
        answ = std::max(curr, answ);
        curr -= arr[l++].cost;
    }
    std::cout << answ;
    return 0;
}