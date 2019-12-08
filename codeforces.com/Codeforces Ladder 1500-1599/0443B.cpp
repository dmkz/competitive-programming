/*
    Problem: 443B. Kolya and Tandem Repeat
    Solution: brute force, implementation, strings
*/
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string s; std::cin >> s;
    int n = (int)s.size(), k; std::cin >> k;
    if (k >= n) {
        std::cout << (n + k) / 2 * 2;
        return 0;
    }
    int answ = 2*k;
    for (int len = k+1; ; ++len) {
        int s1 = n-(len-k);
        int s2 = s1-len;
        if (s1 < 0) break;
        bool flag = true;
        while (s1 < n) {
            if (s[s1] != s[s2]) {
                flag = false;
                break;
            }
            ++s1, ++s2;
        }
        if (flag) {
            answ = std::max(answ, 2*len);
        }
    }
    for (int len = 1; 2*len <= n; ++len) {
        for (int i = 0; i + 2 * len - 1 < n; ++i) {
            if (s.substr(i, len) == s.substr(i+len,len)) {
                answ = std::max(answ, 2*len);
            }
        }
    }
    std::cout << answ;
    return 0;
}