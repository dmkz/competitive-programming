/*
    Problem: 363C. Fixing Typos
    
    Solution: strings, greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>

struct Pair { char item; int count; };

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        std::vector<Pair> arr{Pair{s[0], 0}};
        for (auto& it : s) {
            if (it == arr.back().item) {
                arr.back().count++;
            } else {
                arr.push_back(Pair{it, 1});
            }
        }
        for (int i = 0; i < (int)arr.size(); ++i) {
            auto& curr = arr[i];
            curr.count = std::min(curr.count, 2);
            if (i > 0 && curr.count == 2) {
                const auto& prev = arr[i-1];
                if (prev.count == 2) {
                    curr.count = 1;
                }
            }
        }
        s.clear();
        for (const auto& it : arr) {
            s += std::string(it.count, it.item);
        }
        std::cout << s << std::endl;
    }
    return 0;
}