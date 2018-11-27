/*
    Problem: 404D. Minesweeper 1D
    
    Solution: dynamic programming, combinatorics, O(5*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

const int mod = (int)1e9+7;

int& addto(int& a, int b) {
    return (a += b) >= mod ? (a -= mod) : a;
}

int add(int a, int b) {
    return addto(a,b);
}

int& subfm(int &a, int b) {
    return (a -= b) < 0 ? (a += mod) : a;
}

int sub(int a, int b) {
    return subfm(a, b);
}

int& multo(int &a, int b) {
    return a = int(1LL * a * b % mod);
}

int mul(int a, int b) {
    return multo(a,b);
}

int solve(std::string s) {
    const int n = (int)s.size();
    const int BOMB = 0;
    const int NO_WAIT = 1;
    const int WAIT_LEFT = 2;
    const int WAIT_RIGHT = 3;
    const int WAIT_BOTH = 4;
    std::vector<std::vector<int>> cnt(5, std::vector<int>(n));
    if (s[0] == '*' || s[0] == '?') {
        cnt[BOMB][0] = 1;
    }
    if (n > 1 && (s[0] == '1' || s[0] == '?')) {
        cnt[WAIT_RIGHT][0] = 1;
    }
    if (s[0] == '0' || s[0] == '?') {
        cnt[NO_WAIT][0] = 1;
    }
    for (int i = 1; i < n; ++i) {
        if (s[i] == '0' || s[i] == '?') {
            addto(cnt[NO_WAIT][i], cnt[NO_WAIT][i-1]);
            addto(cnt[NO_WAIT][i], cnt[WAIT_LEFT][i-1]);
        }
        if (s[i] == '1' || s[i] == '?') {
            addto(cnt[WAIT_LEFT][i], cnt[BOMB][i-1]);
            addto(cnt[WAIT_RIGHT][i], cnt[WAIT_LEFT][i-1]);
            addto(cnt[WAIT_RIGHT][i], cnt[NO_WAIT][i-1]);
        }
        if (s[i] == '2' || s[i] == '?') {
            addto(cnt[WAIT_BOTH][i], cnt[BOMB][i-1]);
        }
        if (s[i] == '*' || s[i] == '?') {
            addto(cnt[BOMB][i], cnt[BOMB][i-1]);
            addto(cnt[BOMB][i], cnt[WAIT_RIGHT][i-1]);
            addto(cnt[BOMB][i], cnt[WAIT_BOTH][i-1]);
        }
    }
    return add(n > 1 ? cnt[WAIT_LEFT][n-1] : 0, add(cnt[NO_WAIT][n-1],cnt[BOMB][n-1]));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}