/*
    Problem: 313C. Ilya and Matrix
    
    Solution: constructive, recursion, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

ll solve(int begin, int after, std::vector<int>& items) {
    static std::vector<std::vector<int>> buffer(4, std::vector<int>(1 << 19));
    ll ret = items[begin];
    if (begin + 1 != after) {
        for (int i = begin; i < after; ++i) {
            buffer[i & 3][(i - begin) >> 2] = items[i];
        }
        int side = (after - begin) / 4;
        for (int i = begin; i < begin + side; ++i) {
            items[i] = buffer[0][i-begin];
        }
        for (int i = begin + side; i < begin + 2 * side; ++i) {
            items[i] = buffer[1][i-begin-side];
        }
        for (int i = begin + 2 * side; i < begin + 3 * side; ++i) {
            items[i] = buffer[2][i-begin-2*side];
        }
        for (int i = begin + 3 * side; i < after; ++i) {
            items[i] = buffer[3][i-begin-3*side];
        }
        ret += solve(begin, begin + side, items);
        ret += solve(begin + side, begin + 2 * side, items);
        ret += solve(begin + 2 * side, begin + 3*side, items);
        ret += solve(begin + 3 * side, after, items);
    }
    return ret;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int nItems; 
    while (std::cin >> nItems) {
        std::vector<int> items(nItems);
        for (auto& it : items) { std::cin >> it; }
        std::sort(items.begin(),items.end(), std::greater<int>());
        std::cout << solve(0, nItems, items) << std::endl;
    }
    return 0;
}