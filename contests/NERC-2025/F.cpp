// теория игр, перебор вариантов, поиск закономерности
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using vi = std::vector<int>;

// Решение задачи перебором всех вариантов (исследование дерева игры):
std::map<std::pair<vi, int>, bool> cache;
bool dfs(vi a, int i) {
// если i >= 0, то мы должны уменьшить i-ю кучку и выбрать для противника кучку
    assert(i >= 0);
    int sum = std::accumulate(all(a), 0);
    if (a[i] == sum)
        return cache[{a,i}] = true;
    if (auto it = cache.find({a,i}); it != cache.end())
        return it->second;
    // выбираем шаг:
    for (int x = 1; x <= a[i]; x++)
        // выбираем следующую кучку
        for (int j = 0; j < isz(a); j++) {
            a[i] -= x;
            if (a[j] > 0 && !dfs(a, j)) {
                a[i] += x;
                return cache[{a,i}] = true;
            }
            a[i] += x;
        }
    return cache[{a,i}] = false;
}
std::string solve(vi a) {
    std::string answ = "Alice";
    for (int i = 0; i < isz(a); i++)
        if (a[i] > 0 && !dfs(a, i)) {
            answ = "Bob";
            break;
        }
    return answ;
}
// Результат исследования: победитель зависит от количества единиц в векторе
// Если n - чётное, то побеждает Алиса, если число единиц - чётное, но меньше n
// Если n - нечётное, то побеждает Боб, если число единиц - нечётное, но меньше n
std::string fast(vi a) {
    if (isz(a) == 1)
        return "Alice";
    if (isz(a) == 2)
        return *std::min_element(all(a)) == 1 ? "Bob" : "Alice";
    // считаем количество единиц:
    int cnt1 = (int)std::count(all(a), 1);
    if (isz(a) % 2 == 0)
        return cnt1 % 2 == 0 && cnt1 < isz(a) ? "Alice" : "Bob";                
    else
        return cnt1 % 2 == 1 && cnt1 < isz(a) ? "Bob" : "Alice";
}
void solve() {
    int n; std::cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::cout << fast(a) << std::endl;
}
void research() {
    // брутфорс всех векторов длины <= 6 и вывод на экран победителя для поиска формулы
    const int base = 6;
    for (int n = 1; n <= base; n++) {
        std::cout << "n = " << n << ":\n";
        const int limit = (int)std::pow(base, n);
        vi a(n);
        for (int mask = 0; mask < limit; mask++) {
            bool ok = true;
            for (int temp = mask, i = 0; i < n; temp /= base, i++) {
                a[i] = temp % base + 1;
                if (i > 0 && a[i-1] > a[i])
                    ok = false;
            }
            if (ok) {
                for (int i = 0; i < n; i++)
                    std::cout << std::setw(3) << a[i];
                auto slow = solve(a);
                auto ft = fast(a);
                assert(slow == ft);
                std::cout << ": " << slow << std::endl;
            }
        }
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
