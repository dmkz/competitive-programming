#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>

void prepare(std::string& s) {
    for (int i = 0; i < (int)s.size(); ++i) {
        if ('0' <= s[i] && s[i] <= '9') {
            s[i] = s[i] - '0';
        } else if ('a' <= s[i] && s[i] <= 'z') {
            s[i] = s[i] - 'a' + 10;
        } else if ('A' <= s[i] && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 10 + 26;
        }
        s[i]++;
    }
}

std::vector<int> get_powers(const int count, const int base, const int mod) {
    std::vector<int> powers(1+count, 1);
    for (int i = 1; i <= count; ++i) {
        powers[i] = 1LL * powers[i-1] * base % mod;
    }
    return powers;
}

std::vector<int> pref(const std::string& s, const std::vector<int>& powers, const int mod) {
    std::vector<int> pref{0};
    pref.reserve(s.size()+1u);
    for (int i = 0; i < (int)s.size(); ++i) {
        pref.push_back((pref.back() + 1LL * s[i] * powers[i]) % mod);
    }
    return pref;
}

bool is_prime(int n) {
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int next_prime(int value, int steps = 1) {
    while (steps--) {
        while(!is_prime(++value));
    }
    return value;
}

int main() {
    std::srand(std::time(0));
    const int mod1 = next_prime( 1e9, std::rand() % 77 + 33);
    const int mod2 = next_prime(mod1, std::rand() % 77 + 33);
    const int base = 73;
    
    char buf[1+100000];
    scanf("%100000s", buf);
    std::string a(buf);
    scanf("%100000s", buf);
    std::string b(buf);
    int n = (int)b.size();
    b += b;
    prepare(a); prepare(b);
    
    const int mxPow = 2e5;
    auto powers1 = get_powers(mxPow, base, mod1);
    auto powers2 = get_powers(mxPow, base, mod2);
    auto pref1_a = pref(a, powers1, mod1);
    auto pref2_a = pref(a, powers2, mod2);
    auto pref1_b = pref(b, powers1, mod1);
    auto pref2_b = pref(b, powers2, mod2);
    
    std::vector<std::pair<int, int>> hashes;
    hashes.reserve(b.size());
    for (int i = 0; i + n - 1 < (int)b.size(); ++i) {
        const int hash1 = (0LL + pref1_b[i+n] - pref1_b[i] + mod1) * powers1[mxPow - (i + n - 1)] % mod1;
        const int hash2 = (0LL + pref2_b[i+n] - pref2_b[i] + mod2) * powers2[mxPow - (i + n - 1)] % mod2;
        hashes.push_back({hash1, hash2});
    }
    
    std::sort(hashes.begin(), hashes.end());
    
    int answ = 0;
    for (int i = 0; i + n - 1 < (int)a.size(); ++i) {
        const int hash1 = (0LL + pref1_a[i+n] - pref1_a[i] + mod1) * powers1[mxPow - (i + n - 1)] % mod1;
        const int hash2 = (0LL + pref2_a[i+n] - pref2_a[i] + mod2) * powers2[mxPow - (i + n - 1)] % mod2;
        answ += std::binary_search(hashes.begin(), hashes.end(), std::make_pair(hash1, hash2));
    }
    
    printf("%d", answ);
    
    return 0;
}