#include <bits/stdc++.h>
#include <bits/extc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int int64_t
// для надёжности, функция взятия остатка:
auto remainder(auto a, auto mod) {
    auto result = a % mod;
    if (result < 0) result += mod;
    return result;
}
void solve() {
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto &it : a) std::cin >> it;
    // 0 удалений невозможно: S = 0 (mod n)
    // 1 удаление невозможно: S - a[i] = 0 (mod n-1) для любого i => a[i] = S (mod n-1) =>
    // остатки всех элементов равны одному и тому же числу.
    // Похоже, что мы можем добиться неравенства нулю только тогда, когда у нас будет как
    // минимум два различных остатка. Иначе -1
    auto S = std::accumulate(all(a), __int128(0));
    if (remainder(S, n) != 0) { std::cout << n << "\n"; return; }
    std::vector<int> cnt(n);
    for (int i = 1; i < std::min<int>(30, n); i++) { // сколько элементов удаляем
        std::fill(all(cnt), 0);
        for (auto it : a)
            cnt[remainder(it, (n-i))]++;
        int fi = 0;
        while (fi < isz(cnt) && cnt[fi] == 0) fi++;
        int se = fi+1;
        while (se < isz(cnt) && cnt[se] == 0) se++;
        if (se == isz(cnt)) {
            // только один уникальный остаток: пробуем вычесть его из S ровно i раз
            if (remainder((S - i * fi), (n-i)) != 0) {
                std::cout << n-i << "\n";
                return;
            }
        } else {
            // даже проверять не нужно, всегда можем
            std::cout << n-i << "\n";
            return;
        }
    }
    std::cout << "-1\n";
}
int32_t main() {
    int tt = 1; std::cin >> tt;
    while (tt --> 0) solve();
    return 0;
}