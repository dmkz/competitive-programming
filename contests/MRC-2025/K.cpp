// Задача: K, Вердикт: OK, Время: 5.16s, Память: 184.85Mb
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
using vl = std::vector<ll>;
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvi = std::vector<vi>;
using vvl = std::vector<vl>;
const int SQRT = (int)std::sqrt(2e9+100);
ll getSum(const vl &sums, int from) {
    assert(0 <= from && from < isz(sums));
    return sums.back() - sums[from];
}
main() {
    ll answ{};
    int n; std::cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(all(a));
    vvi values(SQRT);
    vi rems;
    std::vector<bool> visited(SQRT);
    for (int d = 1; d <= SQRT; d++) {
        // складываем по остаткам
        rems.clear();
        for (int i = 0; i < n; i++) {
            int rem = a[i] % d;
            rems.push_back(rem);
            values[rem].push_back(a[i]);
        }
        // values[i] отсортированы по возрастанию для каждого i (по построению)
        for (int rem : rems) {
            if (visited[rem]) continue;
            visited[rem] = true;
            int other = (d - rem);
            if (other >= d)
                other -= d;
            //assert((rem + other) % d == 0);
            if (rem == other) {
                // этот же вектор
                const auto &vec = values[rem];
                // количество пар, которые делятся на d:
                // и чья сумма >= d * d
                int j = isz(vec);
                ll s2 = 0;
                for (int i = 0; i < isz(vec); i++) {
                    // найти j > i у такой что vec[i] + vec[j] >= d * d
                    // vec[j] >= d * d - vec[i]
                    while (j - 1 > i && vec[j-1] >= d * d - vec[i]) {
                        s2 += vec[--j];
                    }
                    if (i == j) {
                        s2 -= vec[j++];
                    }
                    assert(i < j && j <= isz(vec));
                    int cnt = isz(vec) - j;
                    if (!cnt) continue;
                    ll s = s2 + cnt * 1LL * vec[i];
                    answ += cnt * 1LL * d;
                    answ += s / d;
                }
            } else if (rem < other) {
                const auto &vec1 = values[rem];
                const auto &vec2 = values[other];
                if (vec2.empty())
                    continue;
                // разные векторы
                int j = isz(vec2);
                ll s2 = 0;
                for (int i = 0; i < isz(vec1); i++) {
                    // найти j > i у такой что vec[i] + vec[j] >= d * d
                    // vec[j] >= d * d - vec[i]
                    while (j - 1 >= 0 && vec2[j-1] >= d * d - vec1[i])
                        s2 += vec2[--j];
                    assert(0 <= j && j <= isz(vec2));
                    int cnt = isz(vec2) - j;
                    if (!cnt) continue;
                    ll s = s2 + cnt * 1LL * vec1[i];
                    answ += cnt * 1LL * d;
                    answ += s / d;
                }
            }
        }
        for (int rem : rems) {
            if (!visited[rem]) continue;
            visited[rem] = false;
            values[rem].clear();
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) {
            int x = a[i] + a[j];
            int r = (int)std::sqrt(x);
            if (r * r == x)
                answ -= r;
        }
    std::cout << answ << std::endl;
}
