#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>

typedef unsigned long long ull;

std::vector<ull> prepare(std::string& s, const std::vector<ull>& pow) {
    std::vector<ull> pref{0};
    for (int i = 0; i < (int)s.size(); ++i) {
        s[i] = s[i] - 'a' + 1;
        assert(0 < s[i] && s[i] < pow[1]);
        pref.push_back(pref.back() + s[i] * pow[i]);
    }
    return pref;
}

int main() {
    const ull mod = 71;
    std::vector<ull> pow{1};
    while ((int)pow.size() <= 20000) {
        pow.push_back(pow.back() * mod);
    }
    const int mxPow = (int)pow.size()-1;
    
    char buf[1025];
    scanf("%1024s", buf);
    std::string s(buf);
    
    auto pref = prepare(s, pow);
    
    std::vector<ull> hashes;
    for (int i = 0; i < (int)s.size(); ++i) {
        for (int j = i; j < (int)s.size(); ++j) {
            auto hash = (pref[j+1] - pref[i]) * pow[mxPow-j];
            hashes.push_back(hash);
        }
    }
    
    std::sort(hashes.begin(), hashes.end());
    hashes.erase(std::unique(hashes.begin(), hashes.end()), hashes.end());
    
    printf("%d", (int)hashes.size());
    return 0;
}