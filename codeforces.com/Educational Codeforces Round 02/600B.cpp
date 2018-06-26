/*
    Sort + Binary search, O(n log(n))
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int len_a, len_b;
    std::cin >> len_a >> len_b;
    
    std::vector<int> a(len_a), b(len_b);
    for (auto & it : a) {
        std::cin >> it;
    }
    
    for (auto & it : b) {
        std::cin >> it;
    }
    
    std::sort(a.begin(), a.end());
    
    for (auto & it : b) {
        auto jt = std::upper_bound(a.begin(), a.end(), it);
        std::cout << int(jt - a.begin()) << " ";
    }
    
    return 0;
}