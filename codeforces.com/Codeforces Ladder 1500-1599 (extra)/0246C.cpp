/*
    Problem: 246C. Beauty Pageant
    
    Solution: brute force, O(n^2 * k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    std::set<int> sum;
    std::vector<std::vector<int>> answ;
    answ.push_back({0});
    for (int i = 0; i < n; ++i) {
        int m = (int)answ.size();
        for (int j = 0; j < m; ++j) {
            const auto& group = answ[j];
            int s = arr[i];
            for (auto& it : group) s += it;
            if (sum.find(s) == sum.end()) {
                answ.push_back(group);
                answ.back().push_back(arr[i]);
                sum.insert(s);
            }
        }
        if ((int)answ.size() > k) break;
    }
    answ.resize(1+k);
    answ.erase(answ.begin());
    for (auto& row : answ) {
        printf("%d", (int)row.size()-1);
        for (auto& it : row) {
            if (it != 0) {
                printf(" %d", it);
            }
        }
        printf("\n");
    }
    return 0;
}