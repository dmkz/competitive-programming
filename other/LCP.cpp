/*
    Problem: https://www.hackerrank.com/contests/ab-yeh-kar-ke-dikhao/challenges/jitu-and-strings
    
    Solution: polynomial hashes + binary search, O(n * log(n))
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <functional>

typedef unsigned long long ull;

// -----------------------------------------------------------------------------
bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}
// -----------------------------------------------------------------------------
int next_prime(int number, int steps = 1) {
    while (steps--) {
        while (!is_prime(++number));
    }
    return number;
}
// -----------------------------------------------------------------------------

int solve(const std::string& s, const std::string& t) {
    // Constants of hashing:
    const int base = next_prime(256, std::rand() % 77 + 33);
    const int mod1 = next_prime(1e9, std::rand() % 77 + 33);
    const int n = (int)s.size();
    const int mxPow = n;
    
    // Calculation powers of base:
    std::vector<int> pow1(1+mxPow, 1);
    std::vector<ull> pow2(1+mxPow, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = 1LL * pow1[i-1] * base % mod1;
        pow2[i] = pow2[i-1] * base;
    }
    
    // Find hashes on prefixes s and t:
    std::vector<int> s_pref1{0}, t_pref1{0};
    std::vector<ull> s_pref2{0}, t_pref2{0};
    for (int i = 0; i < n; ++i) {
        // Hash modulo mod1:
        s_pref1.push_back((s_pref1.back() + 1LL * s[i] * pow1[i]) % mod1);
        t_pref1.push_back((t_pref1.back() + 1LL * t[i] * pow1[i]) % mod1);
        // Hash modulo mod2 = 2^64:
        s_pref2.push_back(s_pref2.back() + s[i] * pow2[i]);
        t_pref2.push_back(t_pref2.back() + t[i] * pow2[i]);
    }
    
    // Find first not equal symbol:
    int f = 0;
    while (f < n && s[f] == t[f]) ++f;
    
    std::function<std::pair<int, ull>(int,int,int)> hash_on_prefix_after_swap = [&] (const int r, const int f, const int l) {
        // Function for calculating polynomial hash on substring s[0..r] after swap s[f] and s[l]
        int hash1 = 0; ull hash2 = 0;
        // Add hash on s[0, f);
        hash1 += s_pref1[std::min(r+1, f)];
        hash2 += s_pref2[std::min(r+1, f)];
        if (r < f) return std::make_pair(hash1, hash2);
        // Add s[l]:
        hash1 = (hash1 + 1LL * s[l] * pow1[f]) % mod1;
        hash2 += s[l] * pow2[f];
        if (r == f) return std::make_pair(hash1, hash2);
        // Add hash on s[f+1, l): 
        hash1 = (0LL + hash1 + s_pref1[std::min(l, r+1)] - s_pref1[f+1] + mod1) % mod1;
        hash2 += s_pref2[std::min(l, r+1)] - s_pref2[f+1];
        if (r < l) return std::make_pair(hash1, hash2);
        // Add s[f]:
        hash1 = (hash1 + 1LL * s[f] * pow1[l]) % mod1;
        hash2 += s[f] * pow2[l];
        if (r == l) return std::make_pair(hash1, hash2);
        // Add s[l+1, r]:
        hash1 = (0LL + hash1 + s_pref1[r+1] - s_pref1[l+1] + mod1) % mod1;
        hash2 += s_pref2[r+1] - s_pref2[l+1];
        return std::make_pair(hash1, hash2);
    };    
    
    // Try to change the first unequal symbol with all that stand after:
    int answ = f;
    for (int l = f+1; l < n; ++l) {
        // Binary search: s[0..low] == t[0..low], s[0..high] != t[0..high]
        int low = f-1, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            auto h1 = hash_on_prefix_after_swap(mid, f, l);
            if (h1.first == t_pref1[mid+1] && h1.second == t_pref2[mid+1]) {
                low = mid;
            } else {
                high = mid;
            }            
        }
        // Update answer:
        answ = std::max(answ, low+1);
    }
    return answ;
}

int main() {
    std::srand(std::time(0));
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; 
    std::cin >> n;
    std::string s, t;
    std::cin >> s >> t;
    assert(s.size() == t.size());
    std::cout << solve(s, t);
    return 0; 
}