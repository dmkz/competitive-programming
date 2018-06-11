#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <iostream>

// Проверка числа n на простоту:
bool is_prime(const int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

// Следующее простое число, большее, чем number. steps - количество шагов
int next_prime(int number, int steps = 1) {
    while (steps--) {
        while (!is_prime(++number));
    }
    return number;
}

int main() {
    std::srand(std::time(0));
    // Генерация модулей для хэширования:
    const int mod1 = next_prime( 1e9, std::rand() % 77 + 33); 
    const int mod2 = next_prime(mod1, std::rand() % 77 + 33);
    const int base = next_prime( 256, std::rand() % 77 + 33);
    const int mxPow = 1e5;
    
    // Предподсчет степеней основания base по двум модулям:
    std::vector<int> powers1(mxPow+1, 1), powers2(mxPow+1, 1);
    for (int i = 1; i <= mxPow; ++i) {
        powers1[i] = 1LL * powers1[i-1] * base % mod1;
        powers2[i] = 1LL * powers2[i-1] * base % mod2;
    }
    
    // Чтение строки на входе:
    char buf[1+100000];
    scanf("%100000s", buf);
    std::string a(buf);
    const int n = (int)a.size();
    
    // Нахождение хэшей на префиксе:
    std::vector<int> pref1{0}, pref2{0};
    for (int i = 0; i < n; ++i) {
        pref1.push_back((pref1.back() + 1LL * a[i] * powers1[i]) % mod1);
        pref2.push_back((pref2.back() + 1LL * a[i] * powers2[i]) % mod2);
    }
    
    // Нахождение хэшей на суффиксе:
    std::vector<int> suff1{0}, suff2{0};
    for (int i = n-1; i >= 0; --i) {
        suff1.push_back((suff1.back() + 1LL * a[i] * powers1[n-1-i]) % mod1);
        suff2.push_back((suff2.back() + 1LL * a[i] * powers2[n-1-i]) % mod2);
    }
    std::reverse(suff1.begin(), suff1.end());
    std::reverse(suff2.begin(), suff2.end());
    
    // Подсчет количества подпалиндромов:
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        // Проверка на то, что строка [c1-len+1, c2+len-1] является палиндромом. Сложность: O(1)
        std::function<bool(int, int, int)> polyndrome = [&](const int c1, const int c2, const int len) {
            const int left = c1-len+1, right = c2+len-1;
            assert(left >= 0 && right < n);
            const int hash1_l = (pref1[c1+1] - pref1[left] + mod1) * 1LL * powers1[mxPow-c1] % mod1;
            const int hash1_r = (suff1[c2] - suff1[right+1] + mod1) * 1LL * powers1[mxPow-(n-1-c2)] % mod1;
            if (hash1_l != hash1_r) {
                return false;
            }
            const int hash2_l = (pref2[c1+1] - pref2[left] + mod2) * 1LL * powers2[mxPow-c1] % mod2;
            const int hash2_r = (suff2[c2] - suff2[right+1] + mod2) * 1LL * powers2[mxPow-(n-1-c2)] % mod2;
            return hash2_l == hash2_r;
        };
        
        // Нахождение при помощи бинпоиска максимального параметра len: строка [c1-len+1, c2+len-1] - палиндром. Сложность: O(log(n))
        std::function<int(int,int)> max_len = [&](const int c1, const int c2) {
            if (a[c1] != a[c2]) {
                return 0;
            }
            int low = 1, high = std::min(c1+1, n-c2);
            if (polyndrome(c1, c2, high)) {
                low = high;
            } else {
                while (high-low > 1) {
                    int mid = (low+high)/2;
                    if (polyndrome(c1, c2, mid)) {
                        low = mid;
                    } else {
                        high = mid;
                    }
                }       
            }            
            return low;
        };
        if (i+1 < n) { // Палиндром четной длины:
            answer += max_len(i, i+1);
        } 
        // Палиндром нечетной длины:
        answer += max_len(i, i);
    }
    std::cout << answer;
    return 0;
}