/*
    Problem: 825D. Suitable Replacement
    
    Solution: binary search, sort by counting, O(n + log(n)*26)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <queue>
#include <functional>
#include <numeric>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s, t; std::cin >> s >> t;
    int n = (int)s.size(), extra = 0;
    std::vector<int> cnt_s(26,0), cnt_t(26,0);
    for (auto& it : s) {
        if (it == '?') {
            extra++;
        } else {
            cnt_s[int(it-'a')]++;
        }
    }
    for (auto& it : t) {
        cnt_t[int(it-'a')]++;
    }
    
    std::function<bool(int, vi&)> can = [&](const int value, vi& need) {
        int rem = extra;
        std::fill(need.begin(), need.end(), 0);
        for (int i = 0; i < 26; ++i) {
            if (1LL * value * cnt_t[i] <= cnt_s[i]) {
                continue;
            } else {
                ll temp = 1LL * value * cnt_t[i] - cnt_s[i];
                if (temp > rem) {
                    return false;
                }
                need[i] = (int)temp;
                rem -= (int)temp;
            }
        }
        return true;
    };
    std::vector<int> need(26,0);
    int low = 0, high = 2*n;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        std::vector<int> temp(26,0);
        if (can(mid, temp)) {
            need = temp;
            low = mid;
        } else {
            high = mid;
        }
    }
    
    extra -= std::accumulate(need.begin(), need.end(), 0);
    need[0] += extra;
    int pos = 0;
    for (auto& it : s) {
        if (it == '?') {
            while (need[pos] == 0) ++pos;
            need[pos]--;
            it = char('a' + pos);
        }
    }
    std::cout << s;
    return 0;
}