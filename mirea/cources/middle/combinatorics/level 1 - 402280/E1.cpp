#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int mod = (int)(1e9+7); // 1'000'000'000+7

int binpow(int a, int64_t n) {
    if (n == 0)
        return 1;
    // n > 0
    if (a == 1)
        return 1;
    // a = a * 1LL * a;
    if (n % 2 == 0) // чёт
        return binpow(a * a % mod, n / 2);
    return a * binpow(a, n-1) % mod;
}

const int NMAX = (int)1e6;

/*
const vector<int> fact = 
    []()
    {
        // вычисление факториалов:
        vector<int> f(NMAX+1, 0);
        f[0] = 1;
        for (int i = 1; i <= NMAX; i++) {
            // i! = i * (i-1)!
            f[i] = int(i * 1LL * f[i-1] % mod);
        }
        return f;
    }();
*/


int fact[NMAX+1], ifact[NMAX+1];

void fill_fact() {
    fact[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        // i! = i * (i-1)!
        fact[i] = i * fact[i-1] % mod;
    }
}

void fill_ifact() {
    ifact[NMAX] = binpow(fact[NMAX], mod-2);
    for (int i = NMAX-1; i >= 0; i--) {
        // 1/i! = (i+1) * 1/(i+1)!
        ifact[i] = (i + 1) * ifact[i+1] % mod;
    }
}

int C(int n, int k) {
    if (k < 0 || k > n || n < 0)
        return 0;
    return fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}

main() {
    fill_fact(); // предподсчёт факториалов
    fill_ifact(); // предподсчёт обратных факториалов
    // читаем данные:
    int n; cin >> n;
    string s; cin >> s;
    // считаем буквы (их количество):
    map<char,int> countLetter;
    for (int i = 0; i < n; i++) {
        countLetter[s[i]]++;
    }
    // считаем ответ:
    int result = 1;
    int freePoses = n;
    for (char c = 'a'; c <= 'z'; c++) {
        result *= C(freePoses, countLetter[c]);
        result %= mod;
        freePoses -= countLetter[c];
    }
    cout << result << endl;
}