/*
    Problem: 632D. Longest Subsequence
    
    Solution: math, number theory, sort, O(n log(n))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> positions(1+m);
    
    for (int i = 1; i <= n; ++i) {
        int value; std::cin >> value;
        if (value <= m) {
            positions[value].push_back(i);
        }
    }
    
    std::vector<int> count(1+m);
    
    for (int i = 1; i <= m; ++i) {
        for (int j = i; j <= m; j += i) {
            count[j] += (int)positions[i].size();
        }
    }
    
    int best = std::max(1, int(std::max_element(count.begin(), count.end()) - count.begin()));
    
    std::vector<int> answer;
    for (int i = 1; i <= m; ++i) {
        if (best % i == 0) {
            for (auto& it : positions[i]) {
                answer.push_back(it);
            }
        }
    }
    std::sort(answer.begin(), answer.end());
    
    std::cout << best << ' ' << answer.size() << '\n';
    for (auto it : answer) {
        std::cout << it << ' ';
    }
    
    return 0;
}