/*
    Problem: 552E. Vanya and Brackets
    
    Solution: greedy, expression parsing, prefix sums, O(15 * n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long double ll;

ll solve(const std::string &s) {
    // Calculate results on each prefix:
    const int n = (int)s.size();
    std::vector<ll> resultBefore(1+n, -1);
    ll result = 0;
    for (int p = 0; p < n; ) {
        assert(s[p] >= '0' && s[p] <= '9');
        ll tmp = ll(s[p] - '0');
        p++;
        while (p < n && s[p] == '*') {
            p++;
            assert(s[p] >= '0' && s[p] <= '9');
            tmp *= (s[p] - '0');
            p++;
        }
        result += tmp;
        resultBefore[p] = result;
        if (p < n) {
            assert(s[p] == '+');
            p++;
        }
    }
    for (int i = 0; i <= n; ++i) {
        if (resultBefore[i] == -1) {
            resultBefore[i] = resultBefore[i-1];
        }
    }
    // We will try to place right bracket before each '*' operation
    for (int p = 0; p < n; ++p) {
        if (s[p] != '*') { continue; }
        assert(s[p] == '*');
        // Calculate right multiplicative coefficient:
        ll mulRT = 1;
        int rt = p;
        while (rt < n && s[rt] == '*') {
            ++rt; assert(s[rt] >= '0' && s[rt] <= '9');
            mulRT *= (s[rt] - '0');
            ++rt;
        }
        int lt = p-1;
        assert(s[lt] >= '0' && s[lt] <= '9');
        // We will try each position to place left bracket:
        ll sum = 0;
        ll term = (s[lt]-'0');
        while (true) {
            assert(s[lt] >= '0' && s[lt] <= '9');
            int i = lt-1;
            // Calculate left multiplicatiove coefficient:
            ll mulLT = 1;
            while (s[i] == '*') {
                i--; assert(s[i] >= '0' && s[i] <= '9');
                mulLT *= (s[i] - '0');
                i--;
            }
            // Update result:
            result = std::max(result, resultBefore[i] + mulLT * (term + sum) * mulRT - resultBefore[rt] + resultBefore.back());
            lt--;
            if (lt <= 1) {
                break;
            }
            // Move left bracket:
            assert(s[lt] == '*' || s[lt] == '+');
            char op = s[lt];
            lt--;
            assert('0' <= s[lt] && s[lt] <= '9');
            if (op == '+') {
                sum += term; 
                term = 0;
                term = (s[lt] - '0');
            } else {
                term *= (s[lt] - '0');
            }
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        s = "0+1*0+" + s + "+0*1+0";
        std::cout << std::setprecision(0) << std::fixed << solve(s) << std::endl;
    }
    return 0;
}