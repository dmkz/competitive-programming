/*
    Problem: 682D. Alyona and Strings
    
    Solution: dynamic programming, strings, O(k*n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int k, n, m;
    std::cin >> n >> m >> k;
    std::string s, t;
    std::cin >> s >> t;
    s = "^" + s + "$";
    t = "#" + t + "%";
    n += 2; m += 2;
    static int maxRight[1024][1024];
    for (int i = n-1; i >= 0; --i) {
        for (int j = m-1; j >= 0; --j) {
            if (s[i] == t[j]) {
                maxRight[i][j] = 1 + maxRight[i+1][j+1];
            } else {
                maxRight[i][j] = 0;
            }
        }
    }
    static int table[11][1024][1024];
    for (int cnt = 1; cnt <= k; ++cnt) {
        for (int i = n-1; i >= 0; --i) {
            for (int j = m-1; j >= 0; --j) {
                int mxr = maxRight[i][j];
                table[cnt][i][j] = std::max({table[cnt][i+1][j], table[cnt][i][j+1], table[cnt-1][i][j], table[cnt-1][i+mxr][j+mxr]+mxr});
            }
        }
    }
    std::cout << table[k][0][0];
    return 0;
}