/*
    Problem: 388B. Fox and Minimal path
    Solution: graphs, constructive, combinatorics, minimal path, O(log(k))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ll = long long;
int main() {
    int k; std::cin >> k;
    if (k == 1) {
        std::cout << "2\nNY\nYN\n";
        return 0;
    }
    // from 1 to 2
    // we can represent k as 1110010101_2, and firstly, we can build graph 
    // with number of paths equal to largest power of two paths
    vi cnt(1+1000), len(1+1000), stack;
    vvi g(1+1000, vi(1+1000, 0));
    int last = 2;
    cnt[2] = 1;
    while (2 * cnt[last] <= k) {
        int u = last + 1, v = last+2;
        stack.push_back(u);
        g[u][last] = g[last][u] = 1;
        g[v][last] = g[last][v] = 1;
        cnt[u] = cnt[v] = cnt[last];
        len[u] = len[v] = len[last]+1;
        int m = last + 3;
        g[m][u] = g[u][m] = 1;
        g[m][v] = g[v][m] = 1;
        cnt[m] = cnt[u] + cnt[v];
        last = m;
        len[m] = len[u] + 1;
    }
    k -= cnt[last];
    g[1][last] = g[last][1] = 1;
    cnt[1] = cnt[last];
    len[1] = len[last]+1;
    // stack contains vertices with number of path equal to each number of two
    // we can build a chain from vertex 1 to stack.front() and connect with needed power of two
    int back = 1;
    for (int bit = isz(stack)-1; bit >= 0; bit--) {
        if (k & (1 << bit)) {
            int need = stack.back();
            while (len[back] - 1 > len[need]) {
                last++;
                g[back][last] = g[last][back] = 1;
                len[last] = len[back]-1;
                back = last;
            }
            g[need][back] = g[back][need] = 1;
        }
        stack.pop_back();
    }
    
    std::cout << last << std::endl;
    for (int u = 1; u <= last; u++) {
        for (int v = 1; v <= last; v++) {
            std::cout << (g[u][v] ? 'Y' : 'N');
        }
        std::cout << "\n";
    }
    return 0;
}