/*
    Problem: Arun sir and his girlfriend!
    
    Link: https://www.hackerrank.com/contests/ab-yeh-kar-ke-dikhao/challenges/arun-sir-and-his-girlfriend/problem
    
    Solution: sorting, implicit prefix tree, binary search, O(n * log(n) * W)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

struct Edge {
    int vertex, cost;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, root; std::cin >> n >> root; --root;
    
    std::vector<std::vector<Edge>> edges(n);
    
    for (int i = 1; i < n; ++i) {
        int u, v, w; std::cin >> u >> v >> w; --u, --v;
        edges[u].push_back(Edge{v,w});
        edges[v].push_back(Edge{u,w});
    }
    
    std::vector<int> s; // after dfs array s contains xor sums from vertices to root
    
    std::function<void(int,int,int)> visit = [&](const int curr, const int parent, const int sum) {        
        s.push_back(sum);
        for (auto& edge : edges[curr]) {
            if (edge.vertex != parent) {
                visit(edge.vertex, curr, sum ^ edge.cost);
            }
        }
    };
    
    visit(root, -1, 0); // run dfs for calculating xor sums from vertices to root
    
    std::sort(s.begin()+1, s.end()); // sort array s: now array s is prefix tree
    
    // Calculate answer:
    int answ = 0;
    for (int i = 1; i+1 < n; ++i) {
        // find max s[i] ^ s[j] for j = i+1 to n-1 in O(log(n) * WORD_WIDTH) using implicit prefix tree
        int l = i+1, r = n-1;
        for (int pow = 31; pow >= 0; --pow) {
            // Binary search: s[low][pow] == 0, s[high][pow] == 1
            int low = l-1, high = r+1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if ((s[mid] >> pow) & 1) {
                    high = mid;
                } else {
                    low = mid;
                }
            }
            if (high == l || low == r) {
                continue;
            }
            if ((s[i] >> pow) & 1) {
                r = low;   // continue on [l, low]
            } else {
                l = low+1; // continue on [low+1, r]
            }
        }
        // Update answer:
        answ = std::max(answ, s[l] ^ s[i]);
    }
    std::cout << answ;
    return 0;
}