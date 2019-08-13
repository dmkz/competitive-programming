/*
    Problem: D. redist
    Solution: greedy, std::priority_queue, O(n log(n))
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::pair<int,int> pii;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vi x(n), y(n);
        for (auto &it : x) { std::cin >> it; }
        for (auto &it : y) { std::cin >> it; }
        std::priority_queue<pii> queue;
        for (int i = 0; i < n; i++) {
            if (x[i] > y[i]) { queue.push(pii{x[i]-y[i], i}); }
        }
        int64_t answ = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] < y[i]) {
                int need = y[i] - x[i];
                while (need > 0) {
                    assert(isz(queue) > 0);
                    auto top = queue.top();
                    queue.pop();
                    int dec = std::min(need, top.first);
                    need -= dec;
                    top.first -= dec;
                    x[top.second] -= dec;
                    x[i] += dec;
                    answ += dec;
                    if (top.first) {
                        queue.push(top);
                    }
                }
            }
            assert(x[i] >= y[i]);
        }
        std::cout << answ << "\n";
    }
    return 0;
}