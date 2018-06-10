#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

typedef unsigned long long ull;

std::vector<ull> prepare(std::string& s, const std::vector<ull>& pow) {
    std::vector<ull> pref{0};
    for (int i = 0; i < (int)s.size(); ++i) {
        auto& it = s[i];
        if ('0' <= it && it <= '9') {
            it = it - '0';
        } else if ('a' <= it && it <= 'z') {
            it = it - 'a' + 10;
        } else if ('A' <= it && it <= 'Z') {
            it = it - 'A' + 10 + 26;
        }
        it++;
        assert(0 < it && it < pow[1]);
        pref.push_back(pref.back() + pow[i] * it);
    }
    return pref;
}

int main() {
    const int mod = 73;
    std::vector<ull> pow{1, mod};
    while ((int)pow.size() <= 300000) {
        pow.push_back(pow.back() * mod);
    }
    char buf[1+100000];
    scanf("%100000s", buf);
    std::string a(buf);
    scanf("%100000s", buf);
    std::string b(buf);
    
    const int n = b.size();
    b += b;
    
    auto pref_a = prepare(a, pow);
    auto pref_b = prepare(b, pow);
    
    std::vector<ull> hashes;
    for (int i = 0; i+n-1 < (int)b.size(); ++i) {
        hashes.push_back((pref_b[i+n]-pref_b[i]) * pow[(int)pow.size()-(i+n)]);
    }
    std::sort(hashes.begin(), hashes.end());
    int answ = 0;
    for (int i = 0; i+n-1 < (int)a.size(); ++i) {
        auto hash = (pref_a[i+n]-pref_a[i]) * pow[(int)pow.size()-(i+n)];
        answ += binary_search(hashes.begin(), hashes.end(), hash);
    }
    printf("%d", answ);
    return 0;
}