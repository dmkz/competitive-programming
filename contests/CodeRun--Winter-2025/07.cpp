#include <bits/stdc++.h>

using vi = std::vector<int>;

const int mod = 998244353;

void addto(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
int mul(int x, int y) {
    return int(x * 1LL * y % mod);
}
void mulby(int &x, int y) {
    x = mul(x, y);
}
int binpow(int a, int n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            mulby(r, a);
        mulby(a, a);
        n >>= 1;
    }
    return r;
}
int inverse(int a) {
    return binpow(a, mod-2);
}
const int NMAX = 200200;
const vi fact = [](){
    vi res(NMAX+1, 1);
    for (int i = 2; i <= NMAX; i++)
        res[i] = mul(res[i-1], i);
    return res;
}();
const vi ifact = [](){
    vi res(NMAX+1, inverse(fact[NMAX]));
    // 1/n! = 1/(n+1)! * (n+1)
    for (int i = NMAX-1; i >= 0; i--)
        res[i] = mul(res[i+1], i+1);
    return res;
}();
int C(int n, int k) {
    if (n < 0 || k < 0 || k > n)
        return 0;
    return mul(fact[n], mul(ifact[k], ifact[n-k]));
}
void solveSlow() {
// это решение работает за O(s) на тест. Более быстрое - ниже.
    int n, s; std::cin >> n >> s;
    int answ = 0;
    for (int max = s; max >= -s; max--) {
        if (max == 0)
            continue;
        // осталось выбрать n-1 позиций
        // min: 0-min <= s => min >= -s
        // min: max-min <= s => min >= max - s
        int min = std::max(0, max) - s;
        int R = max;
        int L = min;
        int len = R - L + 1;
        // максимум повторно выбрать не можем:
        if (L <= max && max <= R)
            len--;
        // ноль тоже не можем:
        if (max != 0 && L <= 0 && 0 <= R)
            len--;
        // считаем ответ:
        addto(answ, mul(C(len, n-1), fact[n]));
    }
    std::cout << answ << std::endl;
}
int sumBinCoeffs(int from, int to, int k) {
// Считает C(from, k) + C(from+1, k) + ... + C(to, k)
    from = std::max(from, k);
    int answ = 0;
    if (from <= to)
        answ = C(to+1, k+1);
    return answ;
}
void solve() {
    int n, s, answ{}; std::cin >> n >> s;
    // при max от s до -1 всегда будет C(s-1, n-1) * n!
    // затем эта штука убывает: C(s-2, n-1) * n!
    addto(answ, mul(s + 1, C(s-1, n-1)));
    addto(answ, sumBinCoeffs(0, s-2, n-1));
    std::cout << mul(answ, fact[n]) << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
