/*
    Problem: 285A. Slightly Decreasing Permutations
    Solution: greedy, implementation
*/
#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> arr(n);
    
    arr[0] = k+1;
    
    for (int i = 1; i <= k; ++i) {
        arr[i] = arr[i-1]-1;
    }
    
    for (int i = k+1; i < n; ++i) {
        arr[i] = arr[0]+(i-k);
    }
    
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    
    return 0;
}