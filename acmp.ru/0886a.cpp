/*
    "Суффиксы": полиномиальный хэш, O(n*log(n))
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cassert>

typedef long long ll;

inline gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int next_prime(int n, int steps = 1) {
    while (steps--) {
        while (!is_prime(++n));
    }
    return n;
}

inline int pow(int a, ll n, int mod) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = 1LL * res * a % mod;
        }
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return res;
}

inline int inv(int a, int mod) {
    return pow(a, mod-2, mod);
}

inline int get_hash(int base, const std::vector<int>& pref, const int mod, int after, ll len) {
    //assert(len % after == 0);
    base = pow(base, after, mod);
    return 1LL * (pow(base, len / after, mod)-1+mod) * inv(base-1+mod, mod) % mod * pref[after] % mod;
}

int main() {
    double t = clock();
    std::srand(std::time(0));
    const int base = next_prime( 256, std::rand() % 77 + 33);
    const int mod1 = next_prime( 1e9, std::rand() % 77 + 33);
    const int mod2 = next_prime(mod1, std::rand() % 77 + 33);
    
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string s(buf);
    
    std::reverse(s.begin(), s.end());
    
    const int size = (int)s.size();
    
    std::vector<int> pref1{0}, pref2{0};
    
    int pow1 = 1, pow2 = 1;
    for (auto it : s) {
        pref1.push_back((pref1.back() + 1LL * it * pow1) % mod1);
        pref2.push_back((pref2.back() + 1LL * it * pow2) % mod2);
        pow1 = 1LL * pow1 * base % mod1;
        pow2 = 1LL * pow2 * base % mod2;
    }
    int answer = 0;
    for (int after = 1; after <= (int)s.size(); ++after) {
        ll lcm = size / gcd(after, size) * 1LL * after;
        auto h1_a = get_hash(base, pref1, mod1, after, lcm);
        auto h1_b = get_hash(base, pref1, mod1,  size, lcm);
        auto h2_a = get_hash(base, pref2, mod2, after, lcm);
        auto h2_b = get_hash(base, pref2, mod2,  size, lcm);
        answer += (h1_a == h1_b) && (h2_a == h2_b);
    }
    printf("%d\n", answer);
    fprintf(stderr, "time = %0.3fs\n", (clock() - t) / CLOCKS_PER_SEC);
    return 0;
}