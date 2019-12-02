/*
    Problem: 464A. No to Palindromes!
    Solution: constructive, strings, palindromes, O(p*n)
*/
#include <bits/stdc++.h>
std::string solve(const int n, const int p, std::string s) {
    for (int i = n-1; i >= 0; --i) {
        bool can = false;
        char fi = i-2 >= 0 ? s[i-2] : '?';
        char se = i-1 >= 0 ? s[i-1] : '?';
        char th = '?';
        for (char c = s[i]+1; c < 'a' + p; c++) {
            if (!(c == fi || c == se)) {
                can = true;
                th = c;
                break;
            }
        }
        if (can) {
            s[i] = th;
            for (int j = i + 1; j < n; j++) {
                fi = j-2 >= 0 ? s[j-2] : '?';
                se = j-1 >= 0 ? s[j-1] : '?';
                th = '?';
                can = false;
                for (char c = 'a'; c < 'a' + p; c++) {
                    if (!(c == fi || c == se)) {
                        can = true;
                        th = c;
                        break;
                    }
                }
                if (can) {
                    s[j] = th;
                } else {
                    return "NO";
                }
            }
            return s;
        }
    }
    return "NO";
}
int main() {
    for (int n, p; std::cin >> n >> p; ) {
        std::string s; std::cin >> s;
        std::cout << solve(n,p,s) << std::endl;
    }
    return 0;
}