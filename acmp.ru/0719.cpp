/*
    "Фотограф-псих": факториалы, остатки от деления
    
    Исследованный факт: пары остатков (a, b) по простым модулям 10^9+7 и 10^9+9 не совпадают для n до 100000.
*/

#include <stdio.h>
#include <algorithm>
#include <string>

int hash(std::string s, const int mod) {
    int pow = 1, res = 0;
    for (auto it : s) {
        res = (res + 1LL * (it - '0') * pow) % mod;
        pow = 1LL * pow * 10 % mod;
    }
    return res;
}

int main() {
    const int mod1 = (1e9)+7, mod2 = (int)1e9+9;
    
    char buf[500001]; 
    scanf("%500000s", buf);
    std::string s(buf);
    std::reverse(s.begin(), s.end());
    
    const int hash1 = hash(s, mod1), hash2 = hash(s, mod2);
    
    int fact1 = 1, fact2 = 1;
    for (int i = 1; i <= 100000; ++i) {
        fact1 = 1LL * fact1 * i % mod1;
        fact2 = 1LL * fact2 * i % mod2;
        if (fact1 == hash1 && fact2 == hash2) {
            printf("%d", i);
            return 0;
        }
    }
    
    throw 1;
}