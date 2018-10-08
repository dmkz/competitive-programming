/*
    Problem: 574A. Bear and Elections
    
    Solution: priority queue, brute force, O(n * log(n) * MAX)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>

int solve(int need, const std::vector<int>& arr) {
    std::priority_queue<int> queue;
    for (int i = 1; i < (int)arr.size(); ++i) {
        queue.push(arr[i]);
    }
    int cnt = 0;
    while (queue.top() >= need) {
        int top = queue.top(); queue.pop();
        cnt += top - need + 1;
        top = need-1;
        queue.push(top);
    }
    while (arr[0] + cnt <= queue.top()) {
        int top = queue.top(); queue.pop();
        cnt++; top--;
        queue.push(top);
    }
    return cnt;
}

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    int min = arr[0];
    int max = *std::max_element(arr.begin(), arr.end());
    int answ = std::accumulate(arr.begin(), arr.end(),0);
    for (int need = min; need <= max+1; ++need) {
        answ = std::min(answ, solve(need, arr));
    }
    std::cout << answ;
    return 0;
}