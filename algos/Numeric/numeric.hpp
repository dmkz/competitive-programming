#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int,int> pii;

namespace Numeric {
    template<typename T, typename N> 
    T pow(T a, N n) {
        T r(1);
        while (n > 0) {
            if (n & 1) { r *= a; }
            a *= a; n >>= 1;
        }
        return r;
    }
    template<int mod>
    struct IntMod {
        int value;
        IntMod(int value_ = 0) : value(value_) {
            if (value >= mod) value -= mod;
            if (value < 0) value += mod;
        }
        IntMod& operator+=(IntMod num) {
            value += num.value;
            if (value >= mod) value -= mod;
            return *this;
        }
        IntMod& operator-=(IntMod num) {
            value -= num.value;
            if (value < 0) value += mod;
            return *this;
        }
        IntMod operator+(IntMod num) const { return IntMod(*this) += num; }
        IntMod operator-(IntMod num) const { return IntMod(*this) -= num; }
        IntMod operator*(IntMod num) const { return IntMod(int(value * 1LL * num.value % mod)); }
        IntMod& operator*=(IntMod num) { return *this = *this * num; }
        IntMod operator/(IntMod num) const { return *this * pow(num, mod-2); }
        IntMod& operator/=(IntMod num) { return *this = *this / num; }
    };
    template<int mod> bool operator<(IntMod<mod> a,IntMod<mod> b) { return a.value < b.value; }
    template<int mod>
    std::ostream& operator<<(std::ostream& os, const IntMod<mod>& num) {
        return os << num.value;
    }
}

namespace Numeric {
    int addmod(int a, int b, int mod);
    int submod(int a, int b, int mod);
    int mulmod(int a, int b, int mod);
    int powmod(int x, int64_t n, int mod);
    int totient(int x);
    int gcd(int a, int b);
    vi primeDivisors(int x);
    int primitiveRoot(const int mod);
    int logmod(int root, int y, const int mod);
}

namespace Numeric {
    int addmod(int a, int b, int mod) { return (a += b) >= mod ? a -= mod : a; }
    int submod(int a, int b, int mod) { return (a -= b) < 0 ? a += mod : a; }
    int mulmod(int a, int b, int mod) { return int(1LL * a * b % mod); }
    int powmod(int x, int64_t n, int mod) {
        if (x < 2) { return x; }
        int res = 1;
        while (n > 0) {
            if (n & 1) { res = mulmod(res,x,mod); }
            n >>= 1; x = mulmod(x,x,mod);
        }
        return res;
    }
    int totient(int x) {
        int res = 1;
        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                int p = 1;
                x /= i;
                while (x % i == 0) {
                    p *= i; x /= i;
                }
                res *= (i - 1) * p;
            }
        }
        if (x > 1) { res *= (x-1); }
        return res;
    }

    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    vi primeDivisors(int x) {
        vi answ;
        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                answ.push_back(i);
                x /= i;
                while (x % i == 0) { x /= i; }
            }
        }
        if (x > 1) { answ.push_back(x); }
        return answ;
    }

    int primitiveRoot(const int mod) {
        int tot = totient(mod);
        vi divs = primeDivisors(tot);
        for (auto &it : divs) {
            it = tot / it;
        }
        for (int i = 2; i < mod; ++i) {
            bool ok = true;
            for (int p : divs) {
                if (powmod(i,p, mod) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int root = i;
                return root;
            }
        }
        return -1;
    }

    int logmod(int root, int y, const int mod) {
        // root ^ x == y
        int k = (int)std::sqrt(mod);
        std::vector<pii> big, small;
        int inv = powmod(root, mod-2, mod);
        small.resize(k);
        small[0] = pii(y, 0);
        for (int i = 1; i < k; ++i) {
            auto prev = small[i-1];
            prev.first = mulmod(prev.first, inv, mod);
            prev.second++;
            small[i] = prev;
        }
        big.resize((mod+k-1)/k);
        int rootK = powmod(root,k, mod);
        big[0] = pii(1, 0);
        for (int i = 1; i < isz(big); ++i) {
            big[i].first = mulmod(big[i-1].first, rootK, mod);
            big[i].second = i * k;
        }
        std::sort(all(big));
        std::sort(all(small));
        for (auto &pair : big) {
            auto it = std::lower_bound(all(small), pii(pair.first, 0));
            if (it == small.end() || it->first != pair.first) {
                continue;
            }
            int p = pair.second + it->second;
            assert(powmod(root, p, mod) == y);
            return p;
        }
        return -1;
    }
}