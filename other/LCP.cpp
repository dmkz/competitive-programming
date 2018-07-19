/*
    Problem: Jitu and Strings
    
    Link: https://www.hackerrank.com/contests/ab-yeh-kar-ke-dikhao/challenges/jitu-and-strings
    
    Solution: rolling hash, hashing, binary search, O(n * log(n))
*/

#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <iostream>

typedef unsigned long long ull;

// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed ^ ull(new ull));
    int base = std::uniform_int_distribution<int>(before+1, after)(mt_rand);
    return base % 2 == 0 ? base-1 : base;
}

struct PolyHash {
    // -------- Static variables --------
    static const int MOD = 2147483647;
    static std::vector<int> pow1;        // powers of base modulo mod
    static std::vector<ull> pow2;        // powers of base modulo 2^64
    static int base;                     // base (point of hashing)
    
    // --------- Static functons --------
    static inline int diff(int a, int b) { 
    	// Diff between `a` and `b` modulo mod (0 <= a < MOD, 0 <= b < MOD)
        return (a -= b) < 0 ? a + MOD : a;
    }
    
    static inline int mod(ull x) {
        x += MOD;
        x = (x >> 31) + (x & MOD);
        return int((x >> 31) + (x & MOD));
    }
    
    // -------------- Variables of class -------------
    std::vector<int> pref1; // Hash on prefix modulo mod
    std::vector<ull> pref2; // Hash on prefix modulo 2^64
    
    // Cunstructor from string:
    PolyHash(const std::string& s)
        : pref1(s.size()+1u, 0)
        , pref2(s.size()+1u, 0)
    {
        while (pow1.size() <= s.size()) { // Pre-compute powers of base:
            pow1.push_back(mod((ull)pow1.back() * base));
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < (int)s.size(); ++i) { // Fill arrays with polynomial hashes on prefix:
            pref1[i+1] = mod(pref1[i] + (ull)s[i] * pow1[i]);
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
    }
    
    // Polynomial hash of subsequence [pos, pos+len)
    // If mxPow != 0, value automatically multiply on base in needed power. Finally base ^ mxPow
    inline std::pair<int, ull> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = diff(pref1[pos+len], pref1[pos]);
        ull hash2 = pref2[pos+len] - pref2[pos];
        if (mxPow != 0) {
            hash1 = mod((ull)hash1 * pow1[mxPow-(pos+len-1)]);
            hash2 *= pow2[mxPow-(pos+len-1)];
        }
        return std::make_pair(hash1, hash2);
    }
    
    // Polynomial hash on prefix [0, len) after swap items i and j (chars ci and cj):
    inline std::pair<int, ull> prefix_after_swap(const int len, const int i, const int j, const char ci, const char cj) const {
        // Prefix before i:
        int hash1 = pref1[std::min(len, i)];
        ull hash2 = pref2[std::min(len, i)];
        if (len <= i) return std::make_pair(hash1, hash2);
        // Add symbol on position i after swap:
        hash1 = mod(hash1 + (ull)cj * pow1[i]);
        hash2 += cj * pow2[i];
        // Prefix prefore j:
        hash1 = mod(hash1 + (ull)diff(pref1[std::min(len, j)], pref1[i+1]));
        hash2 += pref2[std::min(len,j)] - pref2[i+1];
        if (len <= j) return std::make_pair(hash1, hash2);
        // Add symbol on position j after swap:
        hash1 = mod(hash1 + (ull)ci * pow1[j]);
        hash2 += ci * pow2[j];
        // Prefix before len:
        hash1 = mod(hash1 + (ull)diff(pref1[len], pref1[j+1]));
        hash2 += pref2[len] - pref2[j+1];
        return std::make_pair(hash1, hash2);
    }
};

// Init static variables of PolyHash class:
int PolyHash::base((int)1e9+7);    
std::vector<int> PolyHash::pow1{1};
std::vector<ull> PolyHash::pow2{1};

int solve(const int n, const std::string& s, const std::string& t) {
    // Gen random base of hashing:
    PolyHash::base = gen_base(256, PolyHash::MOD);
    
    // Construct polynomial hashes on prefixes of strings s and t:
    PolyHash hash_s(s), hash_t(t);
    
    // Find first not-equal symbol:
    int pos1 = 0;
    while (pos1 < n && s[pos1] == t[pos1]) ++pos1;
    
    // Try to swap pos1 with everything symbol after and use binary search for finding LCP:
    int answ = pos1;
    for (int pos2 = pos1+1; pos2 < n; ++pos2) {
        // Binary search:
        int low = 0, high = n+1;
        while (high-low > 1) {
            const int mid = (low + high) / 2;
            const auto hs = hash_s.prefix_after_swap(mid, pos1, pos2, s[pos1], s[pos2]);
            if (hs == hash_t(0, mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        // Update answer:
        answ = std::max(answ, low);
    }
    return answ;
}

int main() {
    // Input:
    int n;
    scanf("%d", &n);
    char buf[1+200000];
    scanf("%200000s", buf);
    std::string s(buf);
    scanf("%200000s", buf);
    std::string t(buf);
    // Solve and output:
    printf("%d", solve(n,s,t));
    return 0;
}