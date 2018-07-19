/*
    Problem: 622C. Not Equal on a Segment
    
    Solution: dynamic programming, O(n+q)
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nItems, nQueries; 
    std::cin >> nItems >> nQueries;
    
    std::vector<int> arr(nItems);
    for (auto& it : arr) std::cin >> it;
    
    // Position of first not-equal element on the right side
    std::vector<int> pos(nItems, nItems); 
    for (int i = nItems-2; i >= 0; --i) {
        pos[i] = (arr[i] == arr[i+1]) ? pos[i+1] : i+1;
    }
    // Answer on all queries in O(1) per one query:
    while (nQueries--) {
        int l, r, x;
        std::cin >> l >> r >> x; 
        --l, --r;
        if (arr[l] != x) {
            std::cout << l+1 << '\n';
        } else if (pos[l] > r) {
            std::cout << -1 << '\n';
        } else {
            std::cout << pos[l]+1 << '\n';
        }
    }
    return 0;
}