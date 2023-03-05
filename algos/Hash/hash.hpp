#ifndef __HASH_HPP__
#define __HASH_HPP__
#include <ext/pb_ds/assoc_container.hpp>
#include <random>
#include <chrono>
namespace algos {
namespace hash {
    const ull hash_mod = (ull(1) << 61) - 1; // prime mod of hashing    
    struct Hash {
        ull data{};
        Hash(ull x = 0) : data(x) {
            if (data >= hash_mod) data %= hash_mod;
        }
        Hash operator-() const {
            return Hash(0) -= *this;
        }
        Hash &operator+=(const Hash &a) {
            data += a.data;
            if (data >= hash_mod) data -= hash_mod;
            return *this;
        }
        Hash &operator-=(const Hash &a) {
            data -= a.data;
            if (data >= hash_mod) data += hash_mod;
            return *this;
        }
        Hash &operator*=(const Hash &a) {
            // Calculate (a * b) % mod, 0 <= a < mod, 0 <= b < mod
            ull l1 = (uint32_t)data, h1 = data >> 32, l2 = (uint32_t)a.data, h2 = a.data >> 32;
            ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
            ull ret = (l & hash_mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
            ret = (ret & hash_mod) + (ret >> 61);
            ret = (ret & hash_mod) + (ret >> 61);
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
		Hash operator^(ll n) const {
			while (n < 0) n += hash_mod - 1;
			if (n == 0) return 1;
			if (n == 1 || this->data == 1) return *this;
			Hash r = 1, a = *this;
			while (n > 0) {
				if (n % 2 == 1)
					r *= a;
				a *= a;
				n /= 2;
			}
			return r;
		}
		Hash &operator^=(ll n) {
			return *this = *this ^ n;
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
    
    struct custom_hash
    {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }
    };

    template<typename Key, typename Value>
    using gp_hash_table_custom = __gnu_pbds::gp_hash_table<Key, Value, custom_hash>;
    
    template<typename Key, typename Value>
    using gp_hash_table = __gnu_pbds::gp_hash_table<Key, Value>;
    
} // namespace hash
} // namespace algos
#endif // __HASH_HPP__