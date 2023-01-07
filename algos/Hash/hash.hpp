#ifndef __HASH_HPP__
#define __HASH_HPP__
#include <random>
#include <chrono>
// hash:
namespace hash {
    const ull mod = (ull(1) << 61) - 1; // prime mod of hashing    
    struct Hash {
        ull data{};
        Hash(ull x = 0) : data(x) {
            if (data >= mod) data %= mod;
        }
        Hash operator-() const {
            return Hash(0) -= *this;
        }
        Hash &operator+=(const Hash &a) {
            data += a.data;
            if (data >= mod) data -= mod;
            return *this;
        }
        Hash &operator-=(const Hash &a) {
            data -= a.data;
            if (data >= mod) data += mod;
            return *this;
        }
        Hash &operator*=(const Hash &a) {
            // Calculate (a * b) % mod, 0 <= a < mod, 0 <= b < mod
            ull l1 = (uint32_t)data, h1 = data >> 32, l2 = (uint32_t)a.data, h2 = a.data >> 32;
            ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
            ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
            ret = (ret & mod) + (ret >> 61);
            ret = (ret & mod) + (ret >> 61);
            data = ret-1;
            return *this;
        }
        Hash operator+(const Hash &a) const {
            return Hash(*this) += a;
        }
        Hash operator-(const Hash &a) const {
            return Hash(*this) -= a;
        }
        Hash operator*(const Hash &a) const {
            return Hash(*this) *= a;
        }
        bool operator<(const Hash &a) const {
            return data < a.data;
        }
        friend
        std::ostream &operator<<(std::ostream &os, const Hash &h) { return os << h.data; }
        friend
        std::istream &operator>>(std::istream &os, Hash &h) {
            ull x;
            os >> x;
            h = Hash(x);
            return os;
        }
    };
    GEN_COMPARATORS(Hash)
    std::vector<Hash> basepow{1};
    const Hash base = [](){
        std::uniform_int_distribution<int> dist((int)1.9e9, (int)2e9);
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        int tmp = dist(gen);
        return tmp % 2 == 0 ? tmp - 1 : tmp;
    }();    
    
    struct PolyHash {
        
        // -------- Variables of class --------
        std::vector<Hash> pref; // polynomial hash on prefix
        
        // Constructor from string:
        PolyHash(const std::string& s) 
            : pref(s.size()+1u, 0) 
        {
            // Pre-calculate powers of base:
            while (basepow.size() <= s.size()) {
                basepow.push_back(basepow.back() * base);
            }
            // Calculate polinomial hash on prefix:
            for (int i = 0; i < (int)s.size(); ++i) {
                pref[i+1] = pref[i] * base + s[i];
            }
        }
        
        // Constructor from vector:
        template<typename T> PolyHash(const std::vector<T>& v) 
            : pref(v.size()+1u, 0) 
        {
            // Pre-calculate powers of base:
            while (basepow.size() <= v.size()) {
                basepow.push_back(basepow.back() *  base);
            }
            // Calculate polinomial hash on prefix:
            for (int i = 0; i < (int)v.size(); ++i) {
                pref[i+1] = pref[i] * base + v[i];
            }
        }
        
        // Get hash from [pos, pos+len-1] segment of string
        inline Hash operator()(const int pos, const int len) const {
            return pref[pos+len] - pref[pos] * basepow[len];
        }
    };
}
#endif // __HASH_HPP__