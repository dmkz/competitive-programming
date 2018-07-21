/*
    Problem: 622E. Ants in Leaves
    
    Solution: DFS, greedy, trees, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nVert; std::cin >> nVert;
    
    std::vector<std::vector<int>> edges(nVert);
    for (int i = 1; i < nVert; ++i) {
        int u, v; std::cin >> u >> v;
        edges[u-1].push_back(v-1);
        edges[v-1].push_back(u-1);
    }
    
    std::vector<int> arr;
    
    std::function<void(int,int,int)> visit = [&](const int curr, const int parent, const int depth) {
        if (edges[curr].size() == 1u) {
            // Put depth of leaf in array:            
            arr.push_back(depth);
        }
        for (auto next : edges[curr]) {
            if (next != parent) { // visit all children:
                visit(next, curr, depth+1);
            }
        }
    };
    
    int answ = 0;
    for (auto next : edges[0]) {
        // Get the depth of the leaves in the subtree of the next vertex and sort the values:
        int begin = (int)arr.size();
        visit(next, 0, 1);
        int after = (int)arr.size();
        std::sort(arr.begin()+begin, arr.begin()+after);
        // Get answer for current child:
        int prev = 0;
        for (int i = begin; i < after; ++i) {
            prev = std::max(arr[i], prev+1);
        }
        // Update answer for root:
        answ = std::max(answ, prev);
    }
    std::cout << answ;
    return 0;
}