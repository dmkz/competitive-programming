/*
    Задача: 1197. Количество различных подстрок
     
    Решение: полиномиальный хэш, сортировка, строки, O(n^2 log(n))
     
    Автор: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#pragma GCC optimize ("O3")

#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <array>
#include <iostream>
#include <algorithm>
 
typedef unsigned long long ull;
 
// Generate random seed:
inline ull gen_seed() {
    return ull(new ull) ^ ull(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}
 
// Generate random base in (before, after) open interval:
int gen_base(int before, int after) {
    std::mt19937 gen(gen_seed());
    std::uniform_int_distribution<int> dist(before+2, after-1);
    int base = dist(gen);
    return base % 2 == 0 ? base - 1 : base;
}
 
struct PolyHash {
    // -------- Static variables --------
    static const ull mod = (ull(1) << 61) - 1; // prime mod of hashing
    static int base;                           // odd base of hashing
    static std::vector<ull> pow;               // powers of base modulo mod;
     
    // -------- Static functions --------
    static inline ull add(ull a, ull b) {
        // Calculate (a + b) % mod, 0 <= a < mod, 0 <= b < mod
        return (a += b) < mod ? a : a - mod;
    }
     
    static inline ull sub(ull a, ull b) {
        // Calculate (a - b) % mod, 0 <= a < mod, 0 <= b < mod
        return (a -= b) < mod ? a : a + mod;
    }
 
    static inline ull mul(ull a, ull b){
        // Calculate (a * b) % mod, 0 <= a < mod, 0 <= b < mod
        ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
        ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
        ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & mod) + (ret >> 61);
        ret = (ret & mod) + (ret >> 61);
        return ret-1;
    }
     
    // -------- Variables of class --------
    std::vector<ull> pref; // polynomial hash on prefix
     
    // Constructor from string:
    PolyHash(const std::string& s) 
        : pref(s.size()+1u, 0) 
    {
        // Pre-calculate powers of base:
        while (pow.size() <= s.size()) {
            pow.push_back(mul(pow.back(), base));
        }
        // Calculate polinomial hash on prefix:
        for (int i = 0; i < (int)s.size(); ++i) {
            pref[i+1] = add(mul(pref[i], base), s[i]);
        }
    }
     
    // Get hash from [pos, pos+len-1] segment of string
    inline ull operator()(const int pos, const int len) const {
        return sub(pref[pos+len], mul(pref[pos], pow[len]));
    }
     
};
 
// Init static variables of class PolyHash:
int PolyHash::base((int)1e9+7);
std::vector<ull> PolyHash::pow{1};
 
int main() {
    // Generate random base:
    PolyHash::base = gen_base(256, 2e9);
     
    // Input and prepare hashes:
    char buf[3000+1];
    scanf("%3000s", buf);
    std::string s(buf);
     
    // Calculate rolling hashes on prefix:
    PolyHash hash(s);
     
    // Get hashes from all substring and count unique:
    int answer = 0;
    for (int len = 1; len <= (int)s.size(); ++len) {
        std::vector<ull> hashes;
        for (int p = 0; p + len <= (int)s.size(); ++p) {        
            hashes.push_back(hash(p,len));
        }
        std::sort(hashes.begin(), hashes.end());
        answer += int(std::unique(hashes.begin(), hashes.end())-hashes.begin());
    }
    printf("%d", answer);
    return 0;
}