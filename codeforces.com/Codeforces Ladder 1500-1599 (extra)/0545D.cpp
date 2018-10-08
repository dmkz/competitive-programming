/*
    Problem: 545D. Queue
    
    Solution: sorting, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
typedef long long ll;
struct Pair {
    int value, iter;
};
bool operator<(const Pair& a, const Pair& b) {
    return a.value < b.value || (a.value == b.value && a.iter < b.iter);
}
int main() {
    int n; scanf("%d", &n);
    std::deque<Pair> time(n);
    for (auto& it : time) { scanf("%d", &it.value); it.iter = 1; }
    std::sort(time.begin(), time.end());
    ll sum = 0, answ = n;
    while (!time.empty()) {
        int value = time.front().value;
        int iter = time.front().iter;
        time.pop_front();
        if (value < sum) {
            if (iter == 2) {
                answ--;
                sum += value;
            } else {
                time.push_back(Pair{value, iter+1});
            }
        } else {
            sum += value;
        }
    }
    std::cout << answ;
    return 0;
}