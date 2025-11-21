#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

const int NMAX = (int)1e6+10;
const int mod = (int)1e9+7;

ll mul(ll a, ll b) {
    return a * b % mod;
}

ll binpow(ll a, ll n) {
    ll res = 1 % mod;
    while (n > 0) {
        if (n % 2 == 1)
            res = mul(res, a);
        a = mul(a, a);
        n /= 2;
    }
    return res;
}

ll inverse(ll a) {
    return binpow(a, mod-2);
}

// предподсчёт факториалов
const vl fact = [](){
    vl res(NMAX+1, 1);
    for (int i = 2; i <= NMAX; i++)
        res[i] = res[i-1] * i % mod;
    return res;
}(); // вызывается сразу до функции main

// предподсчёт обратных факториалов
const vl ifact = [](){
    // допустим, знаем ifact[n+1] = 1/(n+1)!
    // Тогда мы можем вычислить и 1/n!, умножив ifact[n+1] на (n+1)
    // формула: ifact[n] = (n+1) * ifact[n+1]
    // считаем с конца в начало
    vl res(NMAX+1, 1);
    res.back() = inverse(fact.back());
    for (int i = NMAX-1; i >= 0; i--)
        res[i] = res[i+1] * (i+1) % mod;
    return res;
}(); // вызывается сразу до функции main

main() {
    // считаем количество каждой буквы, тогда ответ считаем по формуле:
    // n! / (cnt[a]! * cnt[b]! * ... * cnt[z]!)
    int n;
    cin >> n;
    string s; cin >> s;
    vector<int> letterCount(26);
    for (auto letter : s)
        letterCount[letter - 'a']++;
    ll answ = fact[n];
    for (int i = 0; i < 26; i++)
        answ = mul(answ, ifact[letterCount[i]]);
    cout << answ << endl;
}
