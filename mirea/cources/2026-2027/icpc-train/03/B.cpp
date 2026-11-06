#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
// модульная арифметика и хеши:
const int mod1 = (int)1e9+7, mod2 = (int)1e9+9;
int mul(int a, int b, int mod) {
    return int((a * 1LL * b) % mod);
}
struct Hash {
    int x{}, y{};
    Hash(int x_, int y_) : x(x_), y(y_) { }
    Hash(int x_ = 0) : Hash(x_ % mod1, x_ % mod2) { }
    Hash operator+(const Hash &h) const { return Hash((x+h.x)%mod1, (y+h.y)%mod2); }
    Hash operator*(const Hash &h) const { return Hash(mul(x, h.x, mod1), mul(y, h.y, mod2)); }
    Hash operator-(const Hash &h) const { return *this + (-h); }
    Hash operator-() const { return Hash((mod1 - x) % mod1, (mod2 - y) % mod2); }
    friend bool operator==(const Hash &h1, const Hash &h2) { return h1.x == h2.x && h1.y == h2.y; } 
};
int random(int a, int b) {
    static mt19937_64 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a,b)(gen);
}
const int NMAX = 1 << 20;
const vector<Hash> power = [](){
    vector<Hash> result(NMAX+1, Hash(1));
    int base1 = random(1000, mod1-10) | 1; // нечётное число всегда лучше
    int base2 = random(1000, mod2-10) | 1; // аналогично
    result[1] = Hash(base1, base2);
    for (int i = 2; i <= NMAX; i++)
        result[i] = result[i-1] * result[1];
    return result;
}();
// решение задачи:
void solve() {
    // читаем входные данные:
    int k; string s;
    cin >> k >> s;
    // предварительно вычисляем полиномиальные хеши, чтобы сравнивать подстроки за O(1):
    const int n = (int)s.size();
    vector<Hash> hashes{Hash(0)};
    for (auto it : s)
        hashes.push_back(hashes.back() * power[1] + Hash(it));
    // вычисление хешей на подотрезке [start, start + len):
    auto getHash = [&](int start, int len) {
        return hashes[start+len] - hashes[start] * power[len];
    };
    // находим все возможные периоды: периодичность проверяем хешами, сравнивая подстроки [0, n-t) и [t, n)
    vector<int> answer;
    for (int period = 1; period <= n; period++)
        if (getHash(0, n-period) == getHash(period, n-period))
            answer.push_back(period);
    // ответ: минимальный период, который подходит под ограничения задачи на k дубликатов:
    bool was = false;
    for (auto it : answer)
        if (it * 1LL * k >= n) {
            cout << it << '\n';
            was = 1;
            break;
        }
    assert(was);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}