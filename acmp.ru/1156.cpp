#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <ctime>

typedef unsigned long long ull;

bool is_prime(const int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int next_prime(int number, int steps = 1) {
    while (steps--) {
        while (!is_prime(++number));
    }
    return number;
}

int main() {
    std::srand(std::time(0));
    
    // Константы полиномиального хэша:
    const int mod1 = next_prime(1e9, std::rand() % 77 + 33);
    const int base = next_prime(256, std::rand() % 77 + 33);
    const int mxPow = 2e5;
    
    // Предподсчет степеней основания base по модулям полиномиального хэширования:
    std::vector<int> pow1(1+mxPow, 1);
    std::vector<ull> pow2(1+mxPow, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = 1LL * pow1[i-1] * base % mod1;
        pow2[i] = pow2[i-1] * base;
    }
    
    // Чтение входных данных:
    char buf[1+100000];
    scanf("%100000s", buf);
    std::string s(buf); //assert(!worst_case(s));
    const int n = s.size();
    s += s;
    
    // Предпосчет полиномиального хэша на префиксе:
    std::vector<int> pref1{0};
    std::vector<ull> pref2{0};
    for (int i = 0; i < (int)s.size(); ++i) {
        pref1.push_back((pref1.back() + 1LL * s[i] * pow1[i]) % mod1);
        pref2.push_back(pref2.back() + s[i] * pow2[i]);
    }
    
    // Поиск минимального сдвига:
    std::vector<int> shifts(n);
    for (int i = 0; i < n; ++i) {
        shifts[i] = i;
    }
    auto min = std::min_element(shifts.begin(), shifts.end(), [&](const int p1, const int p2) {
        if (s[p1] < s[p2]) {
            return true;
        } else if (s[p1] > s[p2]) {
            return false;
        }
        int low = 0, high = n;
        while (high - low > 1) {
            const int mid = (low + high) / 2;
            const auto hash1_a = (0LL + pref1[p1+mid+1] - pref1[p1] + mod1) * pow1[mxPow-(p1+mid)] % mod1;
            const auto hash1_b = (0LL + pref1[p2+mid+1] - pref1[p2] + mod1) * pow1[mxPow-(p2+mid)] % mod1;
            const auto hash2_a = (pref2[p1+mid+1] - pref2[p1]) * pow2[mxPow-(p1+mid)];
            const auto hash2_b = (pref2[p2+mid+1] - pref2[p2]) * pow2[mxPow-(p2+mid)];
            if (hash1_a == hash1_b && hash2_a == hash2_b) {
                low = mid;
            } else {
                high = mid;
            }
        }
        if (low+1 == n) {
            return p1 < p2;
        }
        assert(s[p1+low+1] != s[p2+low+1]);
        return s[p1+low+1] < s[p2+low+1];
    });
    
    s = s.substr(*min, n);
    printf("%s", s.c_str());
    
    return 0;
}