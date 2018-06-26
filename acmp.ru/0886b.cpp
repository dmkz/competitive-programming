/*
    "Суффиксы": минимальный период, полиномиальный хэш, O(n*log(log(n)))
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int next_prime(int n, int s = 1) {
    while (s--) {
        while (!is_prime(++n));
    }
    return n;
}

std::vector<int> divisors(int n) {
    std::vector<int> answ{1}, stack{n};
    for (int i = 2; i * i <= n; ++i) {
        const int j = n / i;
        if (j * i == n) {
            answ.push_back(i);
            stack.push_back(j);
        }
    }
    while (!stack.empty() && stack.back() == answ.back()) {
        stack.pop_back();
    }
    while (!stack.empty()) {
        answ.push_back(stack.back());
        stack.pop_back();
    }
    return answ;
}

int main() {
    // Константы полиномиального хэширования:
    std::srand(std::time(0));
    const int base = next_prime( 256, std::rand() % 33 + 77);
    const int mod1 = next_prime( 1e9, std::rand() % 33 + 77);
    const int mod2 = next_prime(mod1, std::rand() % 33 + 77);
    
    // Предподсчет степеней основания:
    const int mxPow = 2e5;
    std::vector<int> pow1(1+mxPow, 1), pow2(1+mxPow, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = 1LL * pow1[i-1] * base % mod1;
        pow2[i] = 1LL * pow2[i-1] * base % mod2;
    }
    
    // Чтение данных:
    char buf[100001]; 
    scanf("%100000s", buf);
    std::string s(buf);
    std::reverse(s.begin(), s.end());
    const int n = s.size();
    // Вычисление полиномиального хэша на префиксе:
    std::vector<int> pref1{0}, pref2{0};
    for (int i = 0; i < n; ++i) {
        pref1.push_back((pref1.back() + 1LL * s[i] * pow1[i]) % mod1);
        pref2.push_back((pref2.back() + 1LL * s[i] * pow2[i]) % mod2);
    }
    // Нахождение минимального периода:
    for (auto p : divisors(n)) {
        int h1 = 1LL * pref1[p] * pow1[mxPow-p] % mod1;
        int h2 = 1LL * pref2[p] * pow2[mxPow-p] % mod2;
        bool flag = true;
        for (int i = p; i + p - 1 < n; i += p) {
            int t1 = (0LL + pref1[i+p] - pref1[i] + mod1) * pow1[mxPow-(i+p)] % mod1;
            int t2 = (0LL + pref2[i+p] - pref2[i] + mod2) * pow2[mxPow-(i+p)] % mod2;
            if (t1 != h1 || t2 != h2) {
                flag = false;
                break;
            }
        }
        if (flag) {
            printf("%d", n / p);
            return 0;
        }
    }
    printf("1");
    return 0;
}