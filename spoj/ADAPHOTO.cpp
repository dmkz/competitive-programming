/*
    Problem: ADAPHOTO - Ada and Terramorphing
    
    Solution: hashing, rolling hash, binary search, hash table, O(n log(n))
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <array>
#include <iostream>
#include <algorithm>

typedef unsigned long long ull;

int gen_base(int before, int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed ^ ull(new ull));
    std::uniform_int_distribution<int> dist(before+2, after-1);
    int base = dist(gen);
    return base % 2 == 0 ? base - 1 : base;
}

struct HashTable {
    
    static const int mod = 2000177; // 2000177, 3000077, 4000277
    
    const int step;
    
    std::array<ull, mod> data;
    
    inline int get_hash(ull value) const {
        return int((value + step) % mod);
    }
    
    HashTable() : step(gen_base(mod / 10, mod)) {
        for (auto& it : data) it = 0;
    }
    
    void insert(ull value) {
        int hash = get_hash(value);
        while (true) {
            if (data[hash] == value) {
                return;
            }
            if (data[hash] == 0) {
                data[hash] = value;
                return;
            }
            hash += step;
            if (hash >= mod) {
                hash -= mod;
            }
        }
    }
    
    bool search(ull value) const {
        int hash = get_hash(value);
        while (true) {
            if (data[hash] == value) {
                return true;
            }
            if (data[hash] == 0) {
                break;
            }
            hash += step;
            if (hash >= mod) {
                hash -= mod;
            }
        }
        return false;
    }    
};

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

// Solve problem using binary search and hash table in O(n log(n)):
int solve(const std::string& s, const std::string& t) {    
    // Pre-calculate hash:
    PolyHash hash_s(s), hash_t(t);
    // Binary search by len:
    int low = 0, high = std::min((int)s.size(), (int)t.size())+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        // Insert all hashes of segments length mid of string s:
        HashTable hashes;
        for (int i = 0; i + mid - 1 < (int)s.size(); ++i) {
            hashes.insert(hash_s(i, mid));
        }
        // Search all hashes of segments length mid of string t:
        bool success = false;
        for (int i = 0; i + mid - 1 < (int)t.size(); ++i) {
            if (hashes.search(hash_t(i, mid))) {
                success = true;
                break;
            }
        }
        if (success) low = mid; else high = mid;
    }
    return low;
}

void input(std::string& a, std::string& b) {
    char buf[1+1000000];
    scanf("%1000000s", buf);
    a = buf;
    scanf("%1000000s", buf);
    b = buf;
}

void gen(const int n, std::string& s, std::string& t) {
// Generate test length n and answer n / 2
    s.assign(n, 'v');
    t.assign(n, 'v');
    for (int i = 0, j = n-1; i <= j; ++i, --j) {
        s[i] = '~';
        t[j] = '-';
    }
}

int main() {
    // Generate random base:
    PolyHash::base = gen_base(256, 2e9);
    std::string s, t;
    input(s, t);
    std::cout << solve(s,t);
    return 0;
}