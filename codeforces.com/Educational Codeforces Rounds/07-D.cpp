/*
    Problem: 622D. Optimal Number Permutation
    
    Solution: constructive algorithm, O(n)
*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> arr(2*n, n);
    for (int i = 1, pos = 0; i < n; i += 2, ++pos) {
        arr[pos] = arr[pos + n - i] = i;
    }
    for (int i = 2, pos = 2*n-1; i < n; i += 2, --pos) {
        arr[pos] = arr[pos + i - n] = i;
    }
    for (auto it : arr) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    return 0;
}