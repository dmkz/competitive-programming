/*
    Problem: 710E. Generate a String
    
    Solution: dynamic programming, bfs, queue, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <queue>

typedef long long ll;

int main() {
    int n, x, y;
    std::cin >> n >> x >> y;
    std::vector<ll> min(1+n, (ll)1e18L);
    min[1] = x;
    std::queue<std::pair<ll,int>> queue;
    queue.push(std::make_pair(x+y,2));
    for (int i = 2; i <= n; ++i) {
        while (queue.front().second < i) queue.pop();
        min[i] = std::min(min[i-1]+x,queue.front().first + x * (queue.front().second-i));
        queue.push(std::make_pair(min[i]+y,2*i));
    }
    std::cout << min[n];
    return 0;
}