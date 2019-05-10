/*
    Problem: 494B. Obsessive String
    
    Solution: dynamic programming, prefix function, strings, combinatorics, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

#define isz(s) (int)(s).size()

typedef std::vector<int> vi;

const int mod = (int)1e9+7;

int add(int a, int b) { return (a += b) >= mod ? a - mod : a; }

vi prefix(std::string s) {
    vi ret(isz(s)+1,0);
    for (int i = 1, len = 0; i < isz(s); ++i) {
        while (len > 0 && s[len] != s[i]) {
            len = ret[len];
        }
        len += (s[len] == s[i]);
        ret[i+1] = len;
    }
    return ret;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (std::string s, t; std::cin >> s >> t; ) {
        auto pref = prefix(t + "#" + s);
        pref.erase(pref.begin(), pref.begin()+isz(t)+2);
        vi nearest(isz(s)+1, INT_MAX);
        for (int i = isz(s)-1; i >= 0; --i) {
            if (i + isz(t) - 1 < isz(s) && pref[i+isz(t)-1] == isz(t)) {
                nearest[i] = i + isz(t);
            } else {
                nearest[i] = nearest[i+1];
            }
        }
        vi dp(isz(s)+1, 0), sum(isz(s)+1, 0);
        for (int i = isz(s)-1; i >= 0; --i) {
            if (nearest[i] >= isz(s)+1) {
                continue;
            }
            dp[i] = add(dp[i+1], add(sum[nearest[i]], isz(s) - nearest[i] + 1));
            sum[i] = add(sum[i+1], dp[i]);
        }
        std::cout << dp[0] << std::endl;
    }
    return 0;
}