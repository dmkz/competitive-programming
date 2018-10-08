/*
    Problem: 353B. Two Heaps
    
    Solution: greedy, constructive, O(n^2*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <set>

int main() {
    std::vector<std::vector<int>> pos(100);
    int n; std::cin >> n;
    n *= 2;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        int v; std::cin >> v;
        arr[i] = v;
        pos[v].push_back(i);
    }
    std::vector<int> answ(n, 0);
    int size1 = 0, size2 = 0;
    int prev = 2;
    for (int num = 10; num <= 99; ++num) {
        if (pos[num].empty()) {
            continue;
        }
        if (pos[num].size() >= 2u) {
            int p; 
            p = pos[num].back(); pos[num].pop_back();
            answ[p] = 1;
            p = pos[num].back(); pos[num].pop_back();
            answ[p] = 2;     
            size1++, size2++;
        } else {
            int p = pos[num].back(); pos[num].pop_back();
            answ[p] = 3 - prev;
            prev = 3 - prev;
            if (prev == 1) size1++; else size2++;
        }
    }
    for (int num = 10; num <= 99; ++num) {
        while (!pos[num].empty()) {
            int p = pos[num].back(); pos[num].pop_back();
            if (size1 < size2) {
                answ[p] = 1; size1++;
            } else {answ[p] = 2; size2++;}
        }
    }
    assert(size1 == size2);
    std::set<int> set;
    for (int i = 0; i < n; ++i) {
        if (answ[i] != 1) continue;
        for (int j = 0; j < n; ++j) {
            if (answ[j] != 2) continue;
            set.insert(100 * arr[i] + arr[j]);
        }
    }
    printf("%d\n", (int)set.size());
    for (auto& it : answ) printf("%d ", it);
    return 0;
}