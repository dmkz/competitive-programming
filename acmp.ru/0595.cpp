#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>

typedef unsigned long long ull;

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int next_prime(int number, int steps = 1) {
    while (steps--) {
        while (!is_prime(++number));
    }
    return number;
}

int main() {
    std::srand(std::time(0));
    
    // Константы полиномиального хэширования:
    const int base = next_prime(256, std::rand() % 77 + 33);
    const int mod1 = next_prime(1e9, std::rand() % 77 + 33);
    const int mxPow = 100000;
    
    // Предподсчет степеней основания хэширования:
    std::vector<int> pow1(1+mxPow, 1);
    std::vector<ull> pow2(1+mxPow, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = 1LL * pow1[i-1] * base % mod1;
        pow2[i] = pow2[i-1] * base;
    }
    
    // Считываем входные данные:
    char buf[1+50000];
    scanf("%50000s", buf);
    std::string a(buf);
    scanf("%50000s", buf);
    std::string b(buf);
    
    if (a.size() != b.size()) {
        printf("No\n");
        return 0;
    }
    
    assert(a.size() == b.size());
    const int n = a.size();
    
    // Находим полиномиальный хэш от всей строки b:
    int hash1_b = 0;
    ull hash2_b = 0;
    for (int i = 0; i < n; ++i) {
        hash1_b = (hash1_b + 1LL * b[i] * pow1[i]) % mod1;
        hash2_b = hash2_b + b[i] * pow2[i];
    }
    hash1_b = 1LL * hash1_b * pow1[mxPow-(n-1)] % mod1;
    hash2_b *= pow2[mxPow-(n-1)];
    
    // Находим полиномиальный хэш на префиксе и на суффиксе строки a:
    std::vector<int> pref1{0}, suff1{0};
    std::vector<ull> pref2{0}, suff2{0};
    for (int i = 0; i < n; ++i) {
        pref1.push_back((pref1.back() + 1LL * a[i] * pow1[i]) % mod1);
        suff1.push_back((suff1.back() + 1LL * a[n-i-1] * pow1[i]) % mod1);
        pref2.push_back(pref2.back() + a[i] * pow2[i]);
        suff2.push_back(suff2.back() + a[n-i-1] * pow2[i]);
    }
    std::reverse(suff1.begin(), suff1.end());
    std::reverse(suff2.begin(), suff2.end());
    
    // Осуществляем операции в условии задачи, сравнивая полиномиальные хэши от результатов:
    for (int k = 0; k <= (int)a.size(); ++k) {
        auto hash1_a = (0LL + pref1[n] - pref1[k] + mod1 + pow1[k]*(0LL + suff1[0] - suff1[k] + mod1) % mod1) % mod1 * pow1[mxPow-(n-1+k)] % mod1;
        auto hash2_a = (pref2[n] - pref2[k] + pow2[k]*(suff2[0] - suff2[k]))* pow2[mxPow-(n-1+k)];
        if (hash1_a == hash1_b && hash2_a == hash2_b) {
            printf("Yes\n%d\n", k);
            return 0;
        }
    }
    printf("No\n");
    return 0;
}