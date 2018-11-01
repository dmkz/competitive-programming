/*
    Problem: 405D. Toy Sum
    
    Solution: constructive, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef std::vector<int> vi;

vi solve(const vi& set) {
    const int AMAX = (int)1e6;
    std::vector<bool> taken(1+AMAX, false);
    for (auto it : set) { taken[it] = true; }
    int fi = 1;
    vi answ;
    std::vector<bool> visited(1+AMAX, false);
    for (auto it : set) {
        if (visited[it]) continue;
        int x = AMAX - it + 1;
        visited[it] = true;
        if (!taken[x]) {
            answ.push_back(x);
            taken[x] = true;
            continue;
        }
        while (fi <= AMAX && (taken[fi] || taken[AMAX-fi+1])) {fi++;}
        assert(fi <= AMAX);
        visited[AMAX-it+1] = true;
        answ.push_back(fi);
        answ.push_back(AMAX-fi+1);
        taken[fi] = taken[AMAX-fi+1] = true;
    }
    int64_t sum = 0;
    for (auto it : set) {
        sum += it - 1;
    }
    for (auto it : answ) {
        sum -= AMAX - it;
    }
    assert(sum == 0);
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vi set(n);
        for (auto& it : set) { std::cin >> it; }
        auto answ = solve(set);
        std::cout << answ.size() << "\n";
        for (auto& it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}
