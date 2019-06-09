/*
    Problem: 432D. Prefixes and Suffixes
    
    Solution: strings, prefix function, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
typedef std::vector<int> vi;
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s; std::cin >> s; ) {
        vi pref(1+isz(s));
        for (int i = 1, len = 0; i < isz(s); i++) {
            while (len > 0 && s[i] != s[len]) len = pref[len];
            len += (s[i] == s[len]);
            pref[i+1] = len;
        }
        vi cnt(1+isz(s));
        for (int len = 1; len <= isz(s); len++) { cnt[pref[len]]++; }
        for (int len = isz(s); len > 0; --len) {
            cnt[pref[len]] += cnt[len];
        }
        typedef std::pair<int,int> pii;
        std::vector<pii> answ{pii(isz(s), 1)};
        for (int len = pref[isz(s)]; len > 0; len = pref[len]) {
            answ.push_back(pii(len, cnt[len]+1));
        }
        std::reverse(all(answ));
        std::cout << isz(answ) << "\n";
        for (auto p : answ) { std::cout << p.first << ' ' << p.second << '\n'; }
    }
    return 0;
}