/*
    Problem: 1056. Computer Net
    
    Solution: trees, dfs, dynamic programming, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>

#define remax(x, y) if ((y) > (x)) (x) = (y)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int INF = (int)1e9+1;
int main() {
    int n; scanf("%d", &n);
    vvi edges(1+n);
    for (int i = 2; i <= n; ++i) {
        int p; scanf("%d", &p);
        edges[p].push_back(i);
        edges[i].push_back(p);
    }

    vi fi(1+n), se(1+n), arr;
    
    std::function<void(int,int,int)> visit = [&](int u, int p, int h) {
        arr.push_back(h);
        fi[u] = (int)arr.size()-1;
        for (int v : edges[u]) {
            if (v == p) continue;
            visit(v,u,h+1);
        }
        se[u] = (int)arr.size()-1;
    };
    visit(1,0,0);
    int best = INF; vi answ;
    std::function<void(int,int)> dfs = [&](int u, int p) {
        int max = -INF;
        for (int dist : arr) remax(max, dist);
        if (max < best) {
            best = max;
            answ.clear();
        }
        if (max == best) {
            answ.push_back(u);
        }
        // Спускаемся, пересчитывая расстояние:
        for (int v : edges[u]) {
            if (v == p) continue;
            for (int i = 0; i < n; ++i) {
                if (fi[v] <= i && i <= se[v]) {
                    arr[i]--;
                } else arr[i]++;
            }
            dfs(v,u);
            for (int i = 0; i < n; ++i) {
                if (fi[v] <= i && i <= se[v]) {
                    arr[i]++;
                } else arr[i]--;
            }
        }
    };
    dfs(1,0);
    for (auto& it : answ) printf("%d ", it);
    return 0;
}