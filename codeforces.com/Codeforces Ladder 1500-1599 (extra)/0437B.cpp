/*
    Problem: 437B. The Child and Set
    
    Solution: sorting, greedy, bitmasks, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

int lowBit(int number) {
    int answ = 0;
    for (int p = 30; p >= 0; --p) {
        if ((number >> p) & 1) {
            answ = 1 << p;
        }
    }
    return answ;
}

struct Pair {
    
    int number, lb;
    
    Pair(int x = 0) : number(x), lb(lowBit(x)) { }
};

bool operator<(const Pair& a, const Pair& b) {
    return a.lb < b.lb || (a.lb == b.lb && a.number < b.number);
}

int main() {
    int sum, limit;
    scanf("%d %d", &sum, &limit);
    std::vector<Pair> arr;
    for (int i = 1; i <= limit; ++i) {
        arr.push_back(Pair(i));
    }
    std::sort(arr.begin(), arr.end());
    std::vector<int> answ;
    for (int i = (int)limit-1; i >= 0; --i) {
        if (sum >= arr[i].lb) {
            answ.push_back(arr[i].number);
            sum -= arr[i].lb;
        }
    }
    if (sum > 0) { printf("-1"); return 0; }
    printf("%d\n", (int)answ.size());
    for (auto& it : answ) printf("%d ", it);
    return 0;
}