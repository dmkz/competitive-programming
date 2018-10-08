/*
    Problem: 546C. Soldier and Cards
    
    Solution: implementation, std::queue, O(n!)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cassert>

int main() {
    int n, k1, k2;
    std::cin >> n;
    std::cin >> k1;
    std::queue<int> q1, q2;
    for (int i = 0, v; i < k1; ++i) {
        std::cin >> v; q1.push(v);
    }
    std::cin >> k2;
    for (int i = 0, v; i < k2; ++i) {
        std::cin >> v; q2.push(v);
    }
    int nOp = 0;
    while (!q1.empty() && !q2.empty() && nOp < (int)1e7) {
        ++nOp;
        auto v1 = q1.front(); q1.pop();
        auto v2 = q2.front(); q2.pop();
        if (v1 > v2) {
            q1.push(v2);
            q1.push(v1);
        } else {
            assert(v1 < v2);
            q2.push(v1);
            q2.push(v2);
        }
    }
    if (nOp == (int)1e7) { std::cout << -1; return 0; }
    std::cout << nOp << ' ' << (q1.empty() ? "2" : "1");
    return 0;
}