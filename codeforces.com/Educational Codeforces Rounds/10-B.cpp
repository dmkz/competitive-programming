/*
    Problem: 652B. z-sort
    
    Solution: sorting, deque, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    int n; std::cin >> n;
    
    std::deque<int> deque(n); for (auto& it : deque) std::cin >> it;
    std::sort(deque.begin(), deque.end());
    std::vector<int> answer;
    while (!deque.empty()) {
        if (!deque.empty()) {
            if (!answer.empty() && answer.back() < deque.front()) {
                std::cout << "Impossible\n";
                return 0;
            }
            answer.push_back(deque.front());
            deque.pop_front();
        }
        if (!deque.empty()) {
            if (!answer.empty() && answer.back() > deque.back()) {
                std::cout << "Impossible\n";
                return 0;
            }
            answer.push_back(deque.back());
            deque.pop_back();
        }
    }
    for (auto& it : answer) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    return 0;
}