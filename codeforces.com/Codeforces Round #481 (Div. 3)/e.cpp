#include <bits/stdc++.h>

int main() {
    int n, capacity; 
    std::cin >> n >> capacity;
    
    std::vector<int> diff(n); 
    for (auto& it : diff) std::cin >> it;
    
    int curr = 0, min = 0, max = 0;
    for (auto d : diff) {
        curr += d;
        min = std::min(min, curr);
        max = std::max(max, curr);
    }
    
    int low  = min < 0 ? -min : 0;
    int high = capacity-max;
    std::cout << std::max(high - low + 1, 0) << std::endl;
    return 0;
}