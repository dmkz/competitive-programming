/*
    Problem: 427E. Police Patrol
    
    Solution: greedy, math, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;

ll solve(const int n, const int gsize, const vl& pos) {
    vvl rightGroups, leftGroups;
    ll currPos = pos.front();
    for (int i = n-1; i >= 0; --i) {
        if (rightGroups.empty() || (int)rightGroups.back().size() == gsize) {
            rightGroups.push_back({});
        }
        rightGroups.back().push_back(pos[i]);
    }
    ll currSum = 0;
    for (auto& g : rightGroups) {
        currSum += 2 * (g.front() - currPos);
    }
    ll answ = currSum;
    for (int i = 1; i < n; ++i) {
        // Move to right position from currPos:
        if (leftGroups.empty() || (int)leftGroups.back().size() == gsize) {
            leftGroups.push_back({});
        }
        leftGroups.back().push_back(rightGroups.back().back());
        rightGroups.back().pop_back();
        if (rightGroups.back().empty()) {
            rightGroups.pop_back();
        }
        ll delta = pos[i] - currPos;
        currPos = pos[i];
        // Update answer:
        currSum = currSum - 2 * delta * rightGroups.size() + 2 * delta * leftGroups.size();
        answ = std::min(currSum, answ);
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, gsize;
    while (std::cin >> n >> gsize) {
        vl pos(n); for (auto& it : pos) std::cin >> it;
        std::cout << solve(n,gsize,pos) << std::endl;
    }
    return 0;
}