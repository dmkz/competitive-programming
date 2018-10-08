/*
    Problem: 318B. Strings of Power
    
    Solution: strings, binary search, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s; std::cin >> s;
    std::vector<int> pos1, pos2;
    for (int i = 0; i + 4 < (int)s.size(); ++i) {
        if (s.substr(i, 5) == "heavy") pos1.push_back(i);
        if (s.substr(i, 5) == "metal") pos2.push_back(i);
    }
    int64_t answ = 0;
    for (auto& it : pos1) {
        answ += int(pos2.end()-std::lower_bound(pos2.begin(), pos2.end(), it));
    }
    std::cout << answ;
    return 0;
}