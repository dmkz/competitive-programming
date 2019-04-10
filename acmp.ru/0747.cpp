/*
    Задача: 747. Декомпозиция строки
    
    Решение: строки, хеширование, полиномиальный хеш, динамическое программирование, O(n^2*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef unsigned long long ull;

int gen_base(int before, int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed ^ ull(new ull));
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

struct State {
    int result, len, cnt;
};

bool operator<(const State& a, const State& b) {
    return a.result < b.result;
}

int main() {
    // Generate random base:
    PolyHash::base = gen_base(256, 2e9);
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    std::string s; std::cin >> s;
    PolyHash hash(s);
    std::vector<State> dp(isz(s)+1, State{INT_MAX,0,0});
    dp[isz(s)].result = 0;
    for (int i = isz(s)-1; i >= 0; --i) {
        for (int len = 1; i + len - 1 < isz(s); ++len) {
            ull h[20]; int l[20], last = 0;
            h[0] = hash(i, len);
            l[0] = len;
            while (i + l[last] - 1 < isz(s)) {
                #define add PolyHash::add
                #define mul PolyHash::mul
                #define pow PolyHash::pow
                h[last+1] = add(h[last], mul(h[last], pow[l[last]]));
                l[last+1] = 2 * l[last];
                #undef add
                #undef mul
                #undef pow
                last++;
            }
            int p = i + len;
            while (last >= 0) {
                if (p + l[last] - 1 < isz(s) && hash(p, l[last]) == h[last]) {
                    p += l[last];
                }
                --last;
            }
            assert((p-i) % len == 0);
            for (int cnt = 1; cnt <= (p - i) / len; ++cnt) {
                State res{dp[i + cnt * len].result + len, len, cnt};
                dp[i] = std::min(dp[i], res);
            }
        }
    }
    int pos = 0;
    std::cout << dp[pos].result << "\n";
    while (pos < isz(s)) {
        std::cout << s.substr(pos, dp[pos].len) << " " << dp[pos].cnt << "\n";
        pos += dp[pos].len * dp[pos].cnt;
    }
    return 0;
}