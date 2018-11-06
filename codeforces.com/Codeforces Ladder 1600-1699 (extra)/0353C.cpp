/*
    Problem: 353C. Find Maximum
    
    Solution: greedy, number theory, math, prefix sums, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

typedef std::vector<int> vi;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vi arr(n), sum{0};
        for (auto& it : arr) {
            std::cin >> it;
            sum.push_back(sum.back()+it);
        }
        std::string s; std::cin >> s;
        int max = 0, cur = 0;
        for (int i = n-1; i >= 0; --i) {
            if (s[i] == '0') {
                continue;
            }
            // take i-th bit equal a zero:
            max = std::max(max, cur + sum[i]);
            // take i-th bit equal a one:
            cur += arr[i];
        }
        max = std::max(max, cur);
        std::cout << max << std::endl;
    }
    return 0;
}