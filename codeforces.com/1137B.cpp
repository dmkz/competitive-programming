/*
    Problem: 1137B. Camp Schedule
    
    Solution: greedy, strings, prefix function, O(n)
    
    Description: need to calculate maximal suffix that equal to prefix with same len
*/
#include <bits/stdc++.h>
std::string solve(std::string s, std::string t) {
    int n0s = 0, n0t = 0, n1s = 0, n1t = 0;
    for (auto it : s) { n0s += (it == '0'); n1s += (it == '1'); }
    for (auto it : t) { n0t += (it == '0'); n1t += (it == '1'); }
    if (n0s < n0t || n1s < n1t) { return s; }
    std::vector<int> pref(1+(int)t.size());
    int len = 0;
    for (int i = 1; i < (int)t.size(); ++i) {
        while (len > 0 && t[len] != t[i]) { len = pref[len]; }
        len += (t[i] == t[len]);
        pref[i+1] = len;
    }
    int need0 = 0, need1 = 0;
    for (int i = len; i < (int)t.size(); ++i) {
        need0 += (t[i] == '0');
        need1 += (t[i] == '1');
    }
    s = t; n0s -= n0t; n1s -= n1t;
    while (n0s > 0 || n1s > 0) {
        if (n0s >= need0 && n1s >= need1) {
            s += t.substr(len);
            n0s -= need0, n1s -= need1;
        } else if (n0s > 0) { s.push_back('0'); n0s--; }
        else { s.push_back('1'); n1s--; }
    }
    return s;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s, t; std::cin >> s >> t; std::cout << solve(s,t) << std::endl);
    return 0;
}