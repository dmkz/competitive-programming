/*
    Problem: 479D. Long Jumps
    Solution: binary search, greedy, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, l, x, y;
    std::cin >> n >> l >> x >> y;
    
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    
    bool can_x = false, can_y = false;
    for (int i = 0; i < n; ++i) {
        can_x = can_x || std::binary_search(a.begin()+i+1, a.end(), a[i] + x);
        can_y = can_y || std::binary_search(a.begin()+i+1, a.end(), a[i] + y);
    }
    
    if (can_x && can_y) {
        std::cout << 0;
        return 0;
    } else if (can_x) {
        std::cout << "1\n" << y;
        return 0;
    } else if (can_y) {
        std::cout << "1\n" << x;
        return 0;
    } else {
        for (int i = 0; i < n; ++i) {
            if (a[i] - x > 0) {
                can_y = std::binary_search(a.begin(), a.end(), a[i]-x+y);
                can_y = can_y || std::binary_search(a.begin(), a.end(), a[i]-x-y);
                if (can_y) {
                    std::cout << "1\n" << a[i]-x;
                    return 0;
                }
            }
            if (a[i] + x < l) {
                can_y = std::binary_search(a.begin(), a.end(), a[i]+x+y);
                can_y = can_y || std::binary_search(a.begin(), a.end(), a[i]+x-y);
                if (can_y) {
                    std::cout << "1\n" << a[i]+x;
                    return 0;
                }
            }
        }
    }
    std::cout << "2\n" << x << ' ' << y;
    return 0;
}