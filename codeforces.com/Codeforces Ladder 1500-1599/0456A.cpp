/*
    Problem: 456A. Laptops
    Solution: sorting
*/
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<std::pair<int,int>> arr;
    
    for (int i = 0; i < n; ++i) {
        int a, b; std::cin >> a >> b;
        arr.push_back(std::make_pair(a,b));
    }
    std::sort(arr.begin(), arr.end());
    
    int max = arr[0].second;
    for (int i = 1; i < n; ++i) {
        if (max > arr[i].second) {
            std::cout << "Happy Alex";
            return 0;
        }
        max = std::max(arr[i].second, max);
    }
    std::cout << "Poor Alex";
    
    return 0;
}