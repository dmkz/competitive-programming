#include <stdio.h>
#include <functional>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <functional>

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    --s;
    
    std::vector<std::vector<bool>> g(n, std::vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int v; scanf("%d", &v); g[i][j] = (v == 1);
        }
    }
    
    std::vector<int> visited(n, false);
    
    std::function<void(int)> visit = [&](const int curr) {
        visited[curr] = true;
        for (int next = 0; next < n; ++next) {
            if (!visited[next] && g[curr][next]) {
                visited[next] = true;
                visit(next);
            }
        }
    };
    
    visit(s);
    
    printf("%d", std::accumulate(visited.begin(), visited.end(),-1));
    
    return 0;
}