/*
    Problem: 558C. Amr and Chemistry
    
    Solution: math, number theory, greedy, O(n*log^2(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

std::string to_string(int number) {
    std::string ret;
    do {
        ret.push_back(char('0' + (number & 1)));
        number >>= 1;
    } while (number != 0);
    std::reverse(ret.begin(), ret.end());
    return ret;
}

int to_number(std::string s) {
    int ret = 0;
    for (auto& it : s) {
        ret = 2 * ret + (it - '0');
    }
    return ret;
}

int solve(std::vector<int> a) {
    // Find max common bits prefix:
    std::sort(a.begin(), a.end());
    auto mxPref = to_string(a.front());
    for (int i = 1; i < (int)a.size(); ++i) {
        auto temp = to_string(a[i]);
        int j = 0;
        while (j < (int)mxPref.size() && mxPref[j] == temp[j]) ++j;
        mxPref.resize(j);
    }
    // Cut '1' bit in tail of numbers after common bits prefix:
    int add = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        auto temp = to_string(a[i]);
        assert(temp.substr(0, (int)mxPref.size()) == mxPref);
        int j = (int)temp.size()-1, leftPos = (int)temp.size();
        while (j > (int)mxPref.size()-1) {
            if (temp[j] == '1') {
                leftPos = j;
            }
            --j;
        }
        add += (int)temp.size()-leftPos;
        temp.resize(leftPos);
        a[i] = to_number(temp);
    }
    // Calculate answer:
    int opt = to_number(mxPref), min = (int)1e9+1;
    while (opt < (1 << 30)) {
        int cnt = 0;
        for (auto it : a) {
            while (it > opt) { it >>= 1; cnt++; }
            while (it < opt) { it <<= 1; cnt++; }
            assert(it == opt);
        }
        min = std::min(min, cnt);
        opt <<= 1;
    }
    return min+add;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        std::vector<int> a(n);
        for (auto& it : a) scanf("%d", &it);
        printf("%d\n", solve(a));
    }
    return 0;
}