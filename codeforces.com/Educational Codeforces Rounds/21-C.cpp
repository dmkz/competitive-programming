/*
    Problem: 808C. Tea Party
    
    Solution: constructive, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
typedef long long ll;

struct Pair {
    int size, id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, w; std::cin >> n >> w;
    std::vector<Pair> pairs(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> pairs[i].size;
        pairs[i].id = i;
    }
    std::sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) {
        return a.size > b.size || (a.size == b.size && a.id < b.id);
    });
    std::vector<int> answ(n);
    for (auto& it : pairs) {
        int need = (it.size+1)/2;
        if (w < need) { std::cout << -1; return 0; }
        w -= need;
        answ[it.id] = need;
    }
    int p = 0;
    while (w > 0) {
        if (pairs[p].size > answ[pairs[p].id]) {
            answ[pairs[p].id]++;
            w--;
        }
        p = (p + 1) % n;
    }
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}