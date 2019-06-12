/*
    Problem: 113B. Petr#
    
    Solution: rolling hash, strings, sorting, O(n^2 log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef unsigned long long ull;
const ull mod = (ull(1) << 61) - 1;
const ull seed = (ull)(std::chrono::high_resolution_clock::now().time_since_epoch().count());
std::mt19937 gen(seed);
const ull base = std::uniform_int_distribution<ull>(mod/10,mod-10)(gen)^1;
ull mul(ull a, ull b) {
    ull a0 = (uint32_t)a, b0 = (uint32_t)b, a1 = a >> 32, b1 = b >> 32;
    ull high = a1 * b1, mid = a1 * b0 + a0 * b1, low = a0 * b0;
    ull ret = (high << 3) + (mid >> 29) + ((mid << 32) & mod) + (low >> 61) + (low & mod) + 1;
    ret = (ret >> 61) + (ret & mod);
    return (ret >> 61) + (ret & mod) - 1;
}
ull add(ull a, ull b) { return (a += b) >= mod ? a -= mod : a; }
ull sub(ull a, ull b) { return (a -= b) >= mod ? a += mod : a; }
const int NMAX = 2020;
ull Pow[NMAX];
struct Hash {
    std::array<ull, NMAX> data;
    Hash(const std::string& s) {
        data[0] = 0;
        for (int i = 0; i < isz(s); i++) {
            data[i+1] = add(mul(data[i], base), s[i]);
        }
    }
    ull operator()(int s, int l) const {
        return sub(data[s+l], mul(data[s], Pow[l]));
    }
};
int main() {
    Pow[0] = 1;
    for (int i = 1; i < NMAX; i++) {
        Pow[i] = mul(Pow[i-1], base);
    }
    for (std::string s, b, e; std::cin >> s >> b >> e; ) {
        Hash hs(s), hb(b), he(e);
        std::vector<ull> arr;
        const int minLen = std::max(isz(b), isz(e));
        for (int i = 0; i + minLen <= isz(s); i++) {
            if (hs(i, isz(b)) != hb(0, isz(b))) continue;
            for (int j = i + minLen; j <= isz(s); j++) {
                if (hs(j - isz(e), isz(e)) != he(0, isz(e))) continue;
                arr.push_back(hs(i, j - i));
            }
        }
        std::sort(all(arr));
        arr.erase(std::unique(all(arr)), arr.end());
        std::cout << isz(arr) << std::endl;
    }
    return 0;
}