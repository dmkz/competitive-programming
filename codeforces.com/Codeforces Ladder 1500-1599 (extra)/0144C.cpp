/*
    Problem: 144C. Anagram Search
    
    Solution: prefix sums, strings, O(26*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>

int main() {
    std::string s, t;
    std::cin >> s >> t;
    int n = (int)s.size(), m = (int)t.size();
    std::vector<std::vector<int>> pref(26, std::vector<int>(1+n,0));
    for (int c = 0; c < 26; ++c) {
        for (int i = 0; i < n; ++i) {
            pref[c][i+1] = pref[c][i] + (char('a' + c) == s[i]);
        }
    }
    std::vector<int> need(26);
    for (auto c : t) need[c-'a']++;
    std::function<bool(int,int)> check = [&](int pos, int len) {
        std::vector<int> cnt(26);
        for (int c = 0; c < 26; ++c) {
            cnt[c] = pref[c][pos+len] - pref[c][pos];
        }
        int used = std::accumulate(cnt.begin(), cnt.end(), 0);
        for (int c = 0; c < 26; ++c) {
            int diff = std::max(0, need[c] - cnt[c]);
            if (diff > len - used) {
                return false;
            }
            used += diff;
        }
        return used == len;
    };
    int answ = 0;
    for (int pos = 0; pos + m - 1 < n; ++pos) {
        answ += check(pos, m);
    }
    printf("%d", answ);
    return 0;
}