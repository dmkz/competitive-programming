#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = (int)1e9+7;

ll mul(ll a, ll b) {
    return a * b % mod;
}

ll binpow(ll a, ll n) {
    ll res = 1 % mod;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            res = mul(res, a);
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, k;
    cin >> n >> m >> k;

    ll numUniqueLetters;

    if (k == 1 || k > n) {
        // ограничений нет, любую букву можем выбрать как угодно
        numUniqueLetters = n;
    } else if (k == n) {
        // вся строка - палиндром. Первую половину букв выбираем как угодно
        numUniqueLetters = (n + 1) / 2;
    } else if (k % 2 == 0) {
        // если k - чётное, то все символы должны быть равны одной букве
        numUniqueLetters = 1;
    } else {
        // если k - нечётное, то чётные должны быть равны одной букве,
        // а нечётные - другой
        numUniqueLetters = 2;
    }

    cout << binpow(m, numUniqueLetters) << '\n';
}
