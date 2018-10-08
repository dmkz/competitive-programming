/*
    Problem: 445B. DZY Loves Chemistry
    
    Solution: graphs, bfs, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> react(n, std::vector<bool>(n));
    for (int i = 0; i < m; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        react[a][b] = react[b][a] = 1;
    }
    std::vector<int> part(n), size{0}; int nParts = 0; ll answ = 1;
    for (int u = 0; u < n; ++u) {
        if (!part[u]) {
            nParts++;
            part[u] = nParts;
            size.push_back(1);
            std::queue<int> queue;
            queue.push(u);
            while (!queue.empty()) {
                int curr = queue.front(); queue.pop();
                for (int next = 0; next < n; ++next) {
                    if (!part[next] && react[curr][next]) {
                        part[next] = nParts;
                        size[nParts]++;
                        queue.push(next);
                    }
                }
            }
            answ *= ll(1) << (size[nParts]-1);
        }
    }
    std::cout << answ;
    return 0;
}