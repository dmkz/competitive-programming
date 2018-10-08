/*
    Problem: 435B. Pasha Maximizes
    
    Solution: greedy, constructive, O(log(a)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string s; int k;
    std::cin >> s >> k;
    for (int i = 0; i < (int)s.size(); ++i) {
        int max = i;
        for (int j = i+1; j < (int)s.size(); ++j) {
            if (j-i > k) break;
            if (s[j] > s[max]) {
                max = j;
            }
        }
        while (max != i) {
            std::swap(s[max], s[max-1]);
            --k; --max;
        }
    }
    std::cout << s;
    return 0;
}