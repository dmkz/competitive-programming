/*
    Problem: 272B. Dima and Sequence
    
    Solution: implementation, math, std::map, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <map>

int f(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    return f(x >> 1) + (x & 1);
}

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    std::map<int,int> cnt;
    for (int i = 0; i < n; ++i) {
        int v; std::cin >> v;
        arr[i] = f(v);
        cnt[arr[i]]++;
    }
    int64_t answ = 0;
    for (int i = 0; i < n; ++i) {
        cnt[arr[i]]--;
        answ += cnt[arr[i]];
    }
    std::cout << answ;
    return 0;
}