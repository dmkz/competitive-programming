#include <bits/stdc++.h>
#define int int64_t

// быстрое возведение в степень:
int binpow(int a, int n, int mod) {
    int res = 1 % mod;
    while (n > 0) {
        if (n % 2 == 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

// Комбинаторика: факториалы, обратные к ним и биномиальные коэффициенты
const int mod = (int)1e9+7, NMAX = (int)1e6+30;

int fact[NMAX], ifact[NMAX];

const int precalculated = [](){
    // считаем факториалы:
    fact[0] = 1;
    for (int i = 1; i < NMAX; i++)
        fact[i] = fact[i-1] * i % mod;
    // считаем обратные факториалы:
    ifact[NMAX-1] = binpow(fact[NMAX-1], mod-2, mod);
    for (int i = NMAX-2; i >= 0; i--) {
        ifact[i] = ifact[i+1] * (i+1) % mod;
    }
    return true;
}();

int C(int n, int k) {
// число способов выбрать из n доступных мест ровно k
    if (k < 0 || n < 0 || k > n) return 0;
    return fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}

// проверка на то, что число - прекрасное (содержит только нужные цифры)
bool isPerfect(int number, int d1, int d2) {
    do {
        int lastDigit = number % 10;
        number /= 10;
        if (!(lastDigit == d1 || lastDigit == d2))
            return false;
    } while (number > 0);
    return true;
}

int32_t main() {
    int a, b, n;
    std::cin >> a >> b >> n;
    int answ = 0;
    for (int na = 0; na <= n; na++) {
        int sum = na * a + (n - na) * b;
        if(isPerfect(sum, a, b))
            answ += C(n, na);
    }
    std::cout << answ % mod << std::endl;
}