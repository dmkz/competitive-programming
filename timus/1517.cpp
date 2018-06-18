/*
    Решение при помощи бинарного поиска по длине общей подстроки и полиномиального хэша за O(n*log(n)^2).
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

bool is_prime(int number) {
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return number > 1;
}

int next_prime(int number, int steps = 1) {
    while (steps--) {
        while (!is_prime(++number));
    }
    return number;
}

typedef unsigned long long ull;

std::string solve(const std::string& a, const std::string& b) {
    assert(a.size() == b.size());
    const int n = a.size();
    // Посчитаем константы хэширования:
    const int base = next_prime(256, std::rand() % 77 + 33);
    const int mod1 = next_prime(1e9, std::rand() % 77 + 33);
    // Посчитаем степени основания по модулям хэширования:
    const int mxPow = n;
    std::vector<int> pow1(mxPow+1, 1);
    std::vector<ull> pow2(mxPow+1, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = 1LL * pow1[i-1] * base % mod1;
        pow2[i] = pow2[i-1] * base;
    }
    // Посчитаем полиномиальный хэш на префиксах:
    std::vector<int> pref_a_1(1+n), pref_b_1(1+n);
    std::vector<ull> pref_a_2(1+n), pref_b_2(1+n);
    for (int i = 0; i < n; ++i) {
        pref_a_1[i+1] = (pref_a_1[i] + 1LL * a[i] * pow1[i]) % mod1;
        pref_b_1[i+1] = (pref_b_1[i] + 1LL * b[i] * pow1[i]) % mod1;
        pref_a_2[i+1] = pref_a_2[i] + a[i] * pow2[i];
        pref_b_2[i+1] = pref_b_2[i] + b[i] * pow2[i];
    }
    // Бинарный поиск по длине наибольшей общей подстроки с применением хэширования:
    int low = 0, high = n+1, answ = -1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        assert(0 < mid && mid <= n);
        // Складываем все хэши строки a длины mid в массив:
        std::vector<std::pair<int, ull>> hashes;
        for (int i = mid; i <= n; ++i) {
            int hash1 = 1LL * (pref_a_1[i] - pref_a_1[i-mid] + mod1) * pow1[mxPow-(i-1)] % mod1;
            ull hash2 = (pref_a_2[i] - pref_a_2[i-mid]) * pow2[mxPow-(i-1)];
            hashes.push_back(std::make_pair(hash1, hash2));
        }
        std::sort(hashes.begin(), hashes.end());
        // Ищем хэши строки b длины mid среди соответствующих хэшей строки a:
        int pos = -1;
        for (int i = mid; i <= n; ++i) {
            int hash1 = 1LL * (pref_b_1[i] - pref_b_1[i-mid] + mod1) * pow1[mxPow-(i-1)] % mod1;
            ull hash2 = (pref_b_2[i] - pref_b_2[i-mid]) * pow2[mxPow-(i-1)];
            if (std::binary_search(hashes.begin(), hashes.end(), std::make_pair(hash1, hash2))) {
                pos = i-mid;
                break;
            }
        }
        if (pos == -1) {
            high = mid;
        } else {
            answ = pos;
            low = mid;
        }
    }
    if (low == 0) { // совпадений нет
        return std::string();
    }
    assert(answ != -1 && answ+low-1 < n);
    return b.substr(answ, low);
}

int main() {
    std::srand(std::time(0));
    int n;
    scanf("%d", &n);
    char buf[100000+1];
    scanf("%s", buf);
    std::string a(buf);
    scanf("%s", buf);
    std::string b(buf);
    printf("%s", solve(a, b).c_str());
    return 0;
}