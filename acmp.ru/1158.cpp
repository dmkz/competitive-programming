/*
    Решение влоб: 
    
        - Отсортируем подстроки длины n, при этом необходимо сохранить исходный порядок.
        
        - Сравнение двух подстрок выполним за O(log(n)) при помощи бин. поиска + двойного полиномиального хэша.
            
        - Используем то, что до первого различия строки совпадают - условие бин. поиска. Находим позицию первого различия строк.
    
    Параметры хэширования:
        
        - первый модуль - простое случайное число порядка 1e9
        
        - второй модуль 2^64

    Сдвиг представляем как целое число - позиция начала подстроки. 
    
    Для выполнимости устойчивости сортировки в случае совпадения подстрок необходимо сравнивать позиции, в которых они начинаются.
    
    Итого, решение имеет асимптотику O(n*log(n)^2), если сортировка реализована за O(n*log(n))
*/

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
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

int next_prime(int number, int steps = 1) {
    while (steps--) {
        while (!is_prime(++number));
    }
    return number;
}

typedef unsigned long long ull;

int main() {
    std::srand(std::time(0));
    
    // Константы хэширования:
    const int mod1 = next_prime(1e9, std::rand() % 77 + 33);
    const int base = next_prime(256, std::rand() % 77 + 33);
    
    // Предподсчет степеней основания base по модулям mod1 и mod2:
    const int mxPow = 2e5;
    std::vector<int> pow1(mxPow+1, 1); 
    std::vector<ull> pow2(mxPow+1, 1);
    for (int i = 1; i <= mxPow; ++i) {
        pow1[i] = 1LL * pow1[i-1] * base % mod1;
        pow2[i] = pow2[i-1] * base;
    }
    
    // Читаем входные данные и строим полиномиальный хэш на префиксе:
    char buf[1+100000]; 
    scanf("%100000s", buf); 
    std::string s(buf); 
    const int n = s.size();
    s += s;
    std::vector<int> pref1{0}; 
    std::vector<ull> pref2{0};
    for (int i = 0; i < (int)s.size(); ++i) {
        pref1.push_back((pref1.back() + 1LL * s[i] * pow1[i]) % mod1);
        pref2.push_back(pref2.back() + s[i] * pow2[i]);
    }
    std::vector<int> shifts(n);
    for (int i = 0; i < n; ++i) {
        shifts[i] = i;
    }
    // Сортировка циклических сдвигов за O(n*log(n)^2), используя полиномиальные хэши:
    std::stable_sort(shifts.begin(), shifts.end(), [&](const int p1, const int p2) {
        if (s[p1] < s[p2]) {
            return true;
        } else if (s[p1] > s[p2]) {
            return false;
        }
        int low = 0, high = n;
        while (high - low > 1) {
            const int mid = (low + high) / 2;
            const ull hash2_a = (pref2[p1+mid+1] - pref2[p1]) * pow2[mxPow-(p1+mid)];
            const ull hash2_b = (pref2[p2+mid+1] - pref2[p2]) * pow2[mxPow-(p2+mid)];
            const int hash1_a = (0LL + pref1[p1+mid+1] - pref1[p1] + mod1) * pow1[mxPow-(p1+mid)] % mod1;
            const int hash1_b = (0LL + pref1[p2+mid+1] - pref1[p2] + mod1) * pow1[mxPow-(p2+mid)] % mod1;
            if (hash1_a == hash1_b && hash2_a == hash2_b) {
                low = mid;
            } else {
                high = mid;
            }
        }
        if (low+1 == n) {
            return p1 < p2;
        }
        return s[p1+low+1] < s[p2+low+1];
    });
    
    printf("%d\n", int(std::find(shifts.begin(), shifts.end(), 0) - shifts.begin()) + 1);
    std::string answer;
    for (auto p : shifts) {
        answer.push_back(s[p+n-1]);
    }
    printf("%s", answer.c_str());
    return 0;
}