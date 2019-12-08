/*
    Problem: 388A. Fox and Box Accumulation
    Solution: greedy, sorting
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n); 
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    
    std::vector<std::vector<int>> tower;
    
    for (auto& it : arr) {
        bool flag = false;
        for (auto& t : tower) {
            if ((int)t.size() <= it) {
                t.push_back(it);
                flag = true;
                break;
            }
        }
        if (!flag) {
            tower.push_back({it});
        }
    }
    std::cout << tower.size();
    
    return 0;
}