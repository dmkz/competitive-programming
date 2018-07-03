/*
    Solutions: Greedy, Bit representation, O(n log(n)^2)
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>
#include <functional>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, q; std::cin >> n >> q;
    
    std::vector<int> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
    }
    
    std::sort(arr.begin(), arr.end());
    
    std::vector<int> count(31, 0);
    
    // Counting powers in array:
    int pow = 0;
    for (auto & it : arr) {
        while (it > (1 << pow)) ++pow;
        assert(it == (1 << pow));
        count[pow]++;
    }
    
    // Function for one query O(log(n)^2)
    std::function<int(int)> query = [&](int value) {
        std::vector<int> used(31, 0);
        for (int pow = 0; pow < 31; ++pow) {
            if ((value >> pow) & 1) {
                int need = 1 << pow;
                for (int p = pow; need > 0 && p >= 0; --p) {
                    int get = std::min(need / (1 << p), count[p] - used[p]);
                    used[p] += get;
                    need -= get * (1 << p);
                }
                if (need != 0) {
                    return -1;
                }
            }
        }
        return std::accumulate(used.begin(), used.end(), 0);
    };
    // Output answers for each query:
    while (q--) {
        int value; std::cin >> value;
        std::cout << query(value) << '\n';
    }
    
    return 0;
}