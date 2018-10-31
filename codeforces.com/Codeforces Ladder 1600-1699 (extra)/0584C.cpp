/*
    Problem: 584C. Marina and Vasya
    
    Solution: greedy, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

int main() {
    int n, needDiffs;
    while (std::cin >> n >> needDiffs) {
        std::string s, t;
        std::cin >> s >> t;
        int needEquals = n - needDiffs, eq1 = 0, eq2 = 0;
        std::string res(n, '?');
        // Firstly we need to set symbols in not equal positions:
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i]) { continue; }
            if (std::min(eq1, eq2) >= needEquals) {
                break;
            }
            if (eq1 <= eq2) {
                res[i] = s[i];
                eq1++;
            } else {
                res[i] = t[i];
                eq2++;
            }
        }
        // Secondly we need to remove one equal with `s` in case when `eq1` > `eq2`
        if (eq1 > eq2) {
            bool flag = false;
            for (int i = 0; !flag && i < n; ++i) {
                if (s[i] == res[i]) {
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (s[i] != c && t[i] != c) {
                            res[i] = c;
                            flag = true;
                            break;
                        }
                    }
                }
            }
            assert(flag);
            eq1--;
        }
        // Then we need to set symbols on equal positions:
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i] && eq1 < needEquals) {
                res[i] = s[i];
                eq1++, eq2++;                
            } else if (res[i] == '?') {
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (s[i] != c && t[i] != c) {
                        res[i] = c;
                        break;
                    }
                }
            }
        }
        std::cout << (eq1 == eq2 && eq1 == needEquals ? res : "-1") << std::endl;
    }
    return 0;
}