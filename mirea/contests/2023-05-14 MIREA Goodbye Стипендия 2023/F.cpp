#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod = 998244353, NMAX = 500500;

struct Int {
    
    int value;

    Int (int64_t value_ = 0)
    {
        value_ %= mod;
        if (value_ < 0) value_ += mod;
        value = value_;
    }
    
    friend Int operator*(const Int &a, const Int &b) {
        return Int(a.value * 1LL * b.value);
    }
    
    Int &operator+=(const Int & b) {
        value += b.value;
        if (value >= mod) value -= mod;
        return *this;
    }
    
    friend ostream &operator<<(ostream &os, const Int & a) {
        return os << a.value;
    }
    
};

Int binpow(Int a, int64_t n) {
    Int res = 1;
    while (n > 0) {
        if (n % 2 == 1)
            res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

// факториалы:
const auto fact = []()
{
    vector<Int> result(NMAX, 1);
    for (int i = 1; i < NMAX; i++)
        result[i] = result[i-1] * i;
    return result;
}();

// обратные факториалы:
const auto ifact = []()
{
    vector<Int> result(NMAX);
    result[NMAX-1] = binpow(fact[NMAX-1], mod-2);
    for (int i = NMAX-2; i >= 0; i--)
        result[i] = result[i+1] * (i+1);
    return result;
}();

// биномиальный коэффициент:
Int C(int n, int k) {
    if (n < 0 || k > n || k < 0)
        return 0;
    return fact[n] * ifact[k] * ifact[n-k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        // читаем данные:
        int n, k; cin >> n >> k;
        vi a(n);
        for (auto &it : a)
            cin >> it;
        // решаем задачу:
        vvi cnt(31, vi(2,0));
        Int answ = 0;
        for (int bit = 30; bit >= 0; bit--)
        {
            // решаем задачу для каждого бита независимо
            // чтобы ксор в текущем бите был 1, надо выбрать нечётное число
            // элементов с единичным битом, а все остальные - нули
            // 1. считаем сколько элементов с битом 1 и битом 0:
            for (int i = 0; i < n; i++)
                cnt[bit][a[i] >> bit & 1]++;
            // 2. считаем сумму вариантов выбора нечётного числа 1:
            Int coeff = 0;
            for (int cnt1 = 1; cnt1 <= cnt[bit][1]; cnt1+=2)
                coeff += C(cnt[bit][1], cnt1) * C(cnt[bit][0], k-cnt1);
            // 3. добавляем к ответу:
            answ += binpow(2, bit) * coeff;
        }
        cout << answ << '\n';
    }
    return 0;
}