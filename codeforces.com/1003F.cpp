/*
    Solution: Sort, Binary search, Strings, Polynomial hashes, O(n^3)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

typedef unsigned long long ull;

// ---------------------------------------------------------------------------
bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int next_prime(int n, int s = 1) {
    while (s--) {
        while (!is_prime(++n));
    }
    return n;
}
// ---------------------------------------------------------------------------

int main() {
    std::srand(std::time(0));
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nWords;
    std::cin >> nWords;
    
    std::vector<std::string> words(nWords);
    for (auto& it : words) {
        std::cin >> it;
    }
    
    // Sort words from input and delete duplicates:
    auto set = words;
    std::sort(set.begin(), set.end());
    set.erase(std::unique(set.begin(), set.end()), set.end());
    
    // Find id of every word in set:
    std::vector<int> arr(nWords);
    for (int i = 0; i < nWords; ++i) {
        arr[i] = int(std::lower_bound(set.begin(), set.end(), words[i]) - set.begin());
    }
    
    // Prepare constants for polynomial hashing:
    const int base = next_prime(nWords, std::rand() % 77 + 33);
    const int mod1 = next_prime(1e9, std::rand() % 77 + 33);
    const int mxPow = 2 * nWords;
    // Calculate powers of base modulo mod1 and 2^64:
    std::vector<int> pow1(1+mxPow, 1);
    std::vector<ull> pow2(1+mxPow, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = pow1[i-1] * 1LL * base % mod1;
        pow2[i] = pow2[i-1] * base;
    }
    // Calculate polynomial hashes on prefix:
    std::vector<int> pref1{0};
    std::vector<ull> pref2{0};
    for (int i = 0; i < nWords; ++i) {
        pref1.push_back((pref1.back() + 1LL * pow1[i] * arr[i]) % mod1);
        pref2.push_back(pref2.back() + pow2[i] * arr[i]);
    }
    // Count the total length of words on the prefix:
    std::vector<int> sum_len{0};
    for (int i = 0; i < nWords; ++i) {
        sum_len.push_back(sum_len.back() + set[arr[i]].size());
    }
    
    // Calculate answer:
    int answ = sum_len.back() + (nWords-1);
    for (int begin1 = 0; begin1 < nWords; ++begin1) {
        for (int after1 = begin1+1; after1 <= nWords; ++after1) {
            // Polynomial hash from [begin1, after1) sequence:
            const int h1 = (0LL + pref1[after1]-pref1[begin1] + mod1) % mod1 * pow1[mxPow-after1] % mod1;
            const ull h2 = (pref2[after1]-pref2[begin1]) * pow2[mxPow-after1];
            // Find [begin1, after1) sequence  on remaining fragment of the array:
            int begin2 = after1;
            int after2 = begin2 + (after1-begin1);
            int count = 1;
            while (after2 <= nWords) {
                // Polynomial hash from [begin2, after2) sequence:
                const int f1 = (0LL + pref1[after2]-pref1[begin2] + mod1) % mod1 * pow1[mxPow-after2] % mod1;
                const ull f2 = (pref2[after2]-pref2[begin2]) * pow2[mxPow-after2];
                // Compare [begin1, after1) with [begin2, after2):
                if (f1 == h1 && f2 == h2) {
                    ++count;
                    begin2 = after2;
                    after2 += (after1-begin1);
                } else {
                    begin2++;
                    after2++;
                }
            }
            if (count >= 2) { // Update answer:
                const int all = (nWords-1) + sum_len.back();
                const int dec = sum_len[after1] - sum_len[begin1] + (after1-begin1-1);
                const int add = after1-begin1;
                answ = std::min(answ, all - count * (dec-add));
            }
        }
    }
    // Output answer:
    std::cout << answ;
    return 0;
}