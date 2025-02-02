#ifndef __BITSET_HPP__
#define __BITSET_HPP__

inline void setBitAND(uint64_t * __restrict a,
                      const uint64_t * __restrict b,
                      const int sz)
{
    for (int i = 0; i < sz; i++)
        a[i] &= b[i];
}

inline int cntAND(const uint64_t * __restrict a,
                  const uint64_t * __restrict b,
                  const int sz)
{
    int res = 0;
    for (int i = 0; i < sz; i++)
        res += __builtin_popcountll(a[i] & b[i]);
    return res;
}

inline void setBitOR(uint64_t * __restrict a,
                     const uint64_t * __restrict b,
                     const int sz)
{
    for (int i = 0; i < sz; i++)
        a[i] |= b[i];
}

inline int cntOR(const uint64_t * __restrict a,
                 const uint64_t * __restrict b,
                 const int sz)
{
    int res = 0;
    for (int i = 0; i < sz; i++)
        res += __builtin_popcountll(a[i] | b[i]);
    return res;
}

inline void setBitXOR(uint64_t * __restrict a,
                      const uint64_t * __restrict b,
                      const int sz)
{
    for (int i = 0; i < sz; i++)
        a[i] ^= b[i];
}

inline int cntXOR(const uint64_t * __restrict a,
                  const uint64_t * __restrict b,
                  const int sz)
{
    int res = 0;
    for (int i = 0; i < sz; i++)
        res += __builtin_popcountll(a[i] ^ b[i]);
    return res;
}

struct Bitset {

    struct Reference {
        Bitset &b; int i;
        Reference(Bitset &b_, int i_) : b(b_), i(i_) { }
        operator bool() const { return b.test(i); }
        Reference &operator=(bool x) { return (x ? b.set(i) : b.reset(i), *this); }
    };
    
    int n;
    
    std::vector<uint64_t> data;
    
    Bitset(int n_ = 0) : n(n_), data((n+63)/64) { }
    
    Bitset(const std::string &s)
        : Bitset((int)s.size())
    {
        for (int i = 0; i < (int)s.size(); i++)
            if (s[i] == '1')
                set(i);
    }
    
    void reset(int i) { data[i/64] &= ~(1ULL << i % 64); }
    void set(int i) { data[i/64] |= (1ULL << i % 64); }
    void flip(int i) { data[i/64] ^= (1ULL << i % 64); }
    bool test(int i) const { return (data[i/64] >> i % 64) & 1; }
    
    Reference operator[](int i) { return Reference(*this, i); }
    
    uint64_t lastGroupMask() const {
        const int p = n % 64;
        return p == 0 ? ~0ULL : ~((~0ULL) << n % 64);
    }
    void updateLastGroup() {
        if (data.size()) data.back() &= lastGroupMask();
    }
    
    void reset() {
        std::fill(data.begin(), data.end(), 0);
    }
    
    void resetN(int N) {
        // reset segment [0, N)
        const int g = N / 64;
        const int p = N % 64;
        std::fill(data.begin(), data.begin() + g, 0);
        if (p > 0) {
            data[g] &= ((~0ULL) << p);
        }
    }
    
    void set() {
        std::fill(data.begin(), data.end(), ~0ULL);
        updateLastGroup();
    }
    
    void flip() {
        for (auto &it : data) it = ~it;
        updateLastGroup();
    }
    
    bool isAll() const {
        // full groups
        const int nG = n / 64;
        for (int g = 0; g < nG; g++)
            if (data[g] != ~0ULL)
                return false;
        return !(nG * 64 < n && data[nG] != lastGroupMask());
    }
    
    bool isAny() const {
        // full groups
        for (auto it : data)
            if (it != 0)
                return true;
        return false;
    }
    
    bool isNone() const { return !isAny(); }
    
    int count() const {
        int res{};
        for (auto it : data)
            res += __builtin_popcountll(it);
        return res;
    }
    
    int _Find_first_full(const int startG) const {
        // full groups
        const int nG = isz(data);
        for (int g = startG; g < nG; g++)
            if (data[g])
                return g * 64 + __builtin_ctzll(data[g]);
        return n;
    }
    
    int _Find_first() const { return _Find_first_full(0); }
    
    int _Find_next(int i) const {
        if (i+1 >= n)
            return n;
        // full groups
        const int g = (i+1) / 64;
        const int p = (i+1) % 64;
        if (p == 0) return _Find_first_full(g);
        // watch the current group
        if (const auto x = (data[g] >> p); x)
            return __builtin_ctzll(x) + p + g * 64;
        return _Find_first_full(g+1);
    }
    
    std::string to_string() const {
        std::string res;
        res.reserve(n);
        for (int i = 0; i < n; i++)
            res += "01"[test(i)];
        std::reverse(res.begin(), res.end());
        return res;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Bitset &b) {
        return os << b.to_string();
    }
    
    friend std::istream &operator>>(std::istream &is, Bitset &b) {
        std::string s; is >> s; b = Bitset(s);
        return is;
    }
    
    int shrinkToBitset(const Bitset &other) {
        return (n = other.n, data.resize(other.data.size()), (int)data.size());
    }
    
    Bitset &operator&=(const Bitset &other) {
        const int sz = (data.size() >= other.data.size() ? shrinkToBitset(other) : (int)data.size());
        if (sz) setBitAND(&data[0], &other.data[0], sz);
        updateLastGroup();
        return *this;
    }
    
    int countAND(const Bitset &other) const {
        if (n > other.n) return other.countAND(*this);
        return n == 0 ? 0 : cntAND(&data[0], &other.data[0], (int)data.size());
    }
    
    Bitset &operator^=(const Bitset &other) {
        const int sz = shrinkToBitset(other);
        if(sz) setBitXOR(&data[0], &other.data[0], sz);
        updateLastGroup();
        return *this;
    }
    
    Bitset &operator|=(const Bitset &other) {
        const int sz = shrinkToBitset(other);
        if(sz) setBitOR(&data[0], &other.data[0], sz);
        updateLastGroup();
        return *this;
    }
    
    uint64_t getBlock(int i) {
        const int g = i / 64;
        const int p = i % 64;
        if (p == 0) return data[g];
        const int sz = (int)data.size();
        return (data[g] >> p) | (g+1 < sz ? (data[g+1] << (64 - p)) : 0ULL);
    }
    
    Bitset &shiftRightByOne() {
        if (n <= 1) {
            n = 0;
            data.clear();
            return *this;
        }
        data[0] >>= 1;
        for (int g = 1; g < (int)data.size(); g++) {
            const uint64_t x = data[g];
            data[g-1] |= (x & 1ULL) << 63;
            data[g] = (x >> 1);
        }
        n--;
        data.resize((n+63)/64);
        updateLastGroup();
        return *this;
    }
    
    Bitset &shiftRight(int delta) {
        if (delta <= 0) return *this;
        if (n <= delta) {
            n = 0;
            data.clear();
            return *this;
        }
        const int step = delta / 64;
        const int p = delta % 64;
        if (p == 0) {
            data.erase(data.begin(), data.begin()+step);
            n -= delta;
            return *this;
        }
        if (const int g = 0; g + step < (int)data.size()) {
            const uint64_t x = data[g+step];
            data[g] = (x >> p);
        }
        for (int g = 1; g + step < (int)data.size(); g++) {
            const uint64_t x = data[g+step];
            data[g-1] |= (x << (64-p));
            data[g] = (x >> p);
        }
        n -= delta;
        data.resize((n+63)/64);
        updateLastGroup();
        return *this;
    }
    
    Bitset &shiftLeftByOne() {
        n++;
        data.resize((n+63)/64);
        data.back() <<= 1;
        for (int g = (int)data.size()-2; g >= 0; g--) {
            const uint64_t x = data[g];
            data[g+1] |= (x >> 63);
            data[g] = (x << 1);
        }
        updateLastGroup();
        return *this;
    }
    
    Bitset &shiftLeft(int delta) {
        if (delta <= 0) {
            return *this;
        }
        n += delta;
        data.resize((n+63)/64);
        const int p = delta % 64;
        const int step = delta / 64;
        if (p == 0) {
            data.insert(data.begin(), step, 0);
            return *this;
        }
        if (const int g = (int)data.size()-1; g >= step) {
            const uint64_t x = data[g-step];
            data[g] = (x << p);
        }
        for (int g = (int)data.size()-2; g >= step; g--) {
            const uint64_t x = data[g-step];
            data[g+1] |= (x >> (64-p));
            data[g] = (x << p);
        }
        resetN(delta);
        updateLastGroup();
        return *this;
    }
    
    Bitset &operator>>=(const int delta) {
        return shiftRight(delta);
    }
    
    Bitset &operator<<=(const int delta) {
        return shiftLeft(delta);
    }
    
};
#endif // __BITSET_HPP__