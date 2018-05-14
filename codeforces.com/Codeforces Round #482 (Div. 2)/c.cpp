#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
    
    int n, x, y; 
    std::cin >> n >> x >> y;
    --x, --y;
    
    std::vector<std::vector<int>> edges(n);
    
    for (int i = 0; i < n-1; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    std::vector<int> size(n); // size[v] = number of vertex if subtree[v]
    std::vector<bool> is_x(n);// is_x[v] = true if vertex x in subtree[v]
    
    std::function<void(int, int)> visit = [&](const int curr, const int parent) {
        size[curr]++;
        if (curr == x) {
            is_x[curr] = true;
        }
        for (auto next : edges[curr]) {
            if (next != parent) {
                visit(next, curr);
                size[curr] += size[next];
                if (is_x[next] && !is_x[curr]) {
                    is_x[curr] = true;
                }
            }
        }
    };
    
    visit(y, y);
    
    long long sum_without_x = 1;
    long long count_with_x = 0;
    for (auto next : edges[y]) {
        if (!is_x[next]) {
            sum_without_x += size[next];
        } else {
            count_with_x++;
        }
    }
    assert(count_with_x == 1);
    std::cout << 1LL * n * (n-1) - 1LL * size[x] * sum_without_x << std::endl;
    
    return 0;
}