/*
    Problem: 219C. Color Stripe
    Solution: greedy, strings
*/
#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, k;
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;
    
    if (k == 2) {
        std::string t1(n, '?'), t2(n, '?');
        for (int i = 0; i < n; ++i) {
            t1[i] = (i % 2) ? 'A' : 'B';
            t2[i] = (i % 2) ? 'B' : 'A';
        }
        int r1 = 0, r2 = 0;
        for (int i = 0; i < n; ++i) {
            r1 += s[i] != t1[i];
            r2 += s[i] != t2[i];
        }
        if (r1 > r2) {
            std::swap(r1, r2);
            std::swap(t1, t2);
        }
        std::cout << r1 << '\n' << t1;
    } else {
        s.push_back('?');
        int res = 0;
        for (int i = 1; i < n; ++i) {
            if (s[i-1] == s[i]) {
                res++;
                for (char c = 'A'; c < 'A' + k; ++c) {
                    if (c != s[i-1] && c != s[i+1]) {
                        s[i] = c;
                        break;
                    }
                }
            }
        }
        s.pop_back();
        std::cout << res << '\n' << s;
    }
    
    return 0;
}