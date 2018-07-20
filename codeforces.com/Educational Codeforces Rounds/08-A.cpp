/*
    Problem: 628A. Tennis Tournament

    Solution: implementation, O(n log(n))

    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

typedef long long ll;

int main() {
    int n, b, p; std::cin >> n >> b >> p;
    std::vector<int> need_b(n, 0);
    std::queue<int> queue;
    for (int i = 0; i < n; ++i) {
        queue.push(i);
    }
    int calc_b = 0;
    while (queue.size() > 1u) {
        int pow2 = 1;
        while (pow2 * 2 <= int(queue.size())) {
            pow2 *= 2;
        }
        pow2 /= 2;
        std::queue<int> q2;
        for (int k = 0; k < pow2; ++k) {
            int i = queue.front(); queue.pop();
            int j = queue.front(); queue.pop();
            need_b[i] += b;
            need_b[j] += b;
            calc_b += 1;
            q2.push(i);
        }
        while (!queue.empty()) {
            q2.push(queue.front());
            queue.pop();
        }
        queue = q2;
    }
    calc_b += std::accumulate(need_b.begin(), need_b.end(), 0LL);
    std::cout << calc_b << " " << p * n << std::endl;
    
    return 0;
}