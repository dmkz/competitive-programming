/*
    Problem: 219A. k-String
    Solution: implementation, strings
*/
#include <iostream>
#include <vector>
#include <string>
int main() {
    int k; std::cin >> k;
    std::string s;
    std::cin >> s;
    const int n = (int)s.size();
    std::vector<int> count(256, 0);
    for (auto& it : s) count[it]++;
    for (auto& it : count) {
        if (it % k != 0) {
            std::cout << -1;
            return 0;
        }
    }
    std::string t(n, '?');
    int pos = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        while (count[c]) {
            for (int p = pos; p < n; p += n / k) {
                t[p] = c;
                count[c]--;
            }
            ++pos;
        }
    }
    std::cout << t;
    return 0;
}