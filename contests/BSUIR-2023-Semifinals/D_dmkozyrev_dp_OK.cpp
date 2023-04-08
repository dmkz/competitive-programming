#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
using ll = long long;
using vl = std::vector<ll>;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, k; std::cin >> n >> k;
    vl a(n);
    for (auto &it : a)
        std::cin >> it;
    // инициализируем для k = 2: |max-a[i]| или |a[i]-min]
    vl dpCurr(n), dpNext(n);
    ll min = a[0], max = a[0];
    for (int i = 1; i < n; i++) {
        dpCurr[i] = std::max<ll>(std::abs(max-a[i]),std::abs(min-a[i]));
        setmin(min,a[i]);
        setmax(max,a[i]);
    }
    const ll INF = (ll)1e18L;
    // считаем динамику по слоям в порядке возрастания k
    // dp[k][n] = максимальная сумма модулей, если взято k элементов
    // на префиксе [0, n] и n-й элемент обязательно взят
    // dpCurr = слой для k
    // dpNext = слой для k+1
    for (int wave = 2; wave < k; wave++) {
        std::fill(all(dpNext), -INF);
        ll maxPlus = a[wave-1] + dpCurr[wave-1];
        ll maxMinus = -a[wave-1] + dpCurr[wave-1];
        for (int i = wave; i < n; i++) {
            // среди всех, которые больше текущего:
            // a[j] - a[i] + dp[j] -> находим максимум из dp[j] + a[j]
            // среди всех, которые меньше текущего:
            // a[i] - a[j] + dp[j] -> находим максимум из dp[j] - a[j]
            // UPD: можем брать среди всех, так как берём максимум, и если рассмотрим
            // что-то не то, то ответ лишь будет только меньше альтернативы и мы им
            // не воспользуемся
            dpNext[i] = std::max(a[i]+maxMinus, -a[i]+maxPlus);
            setmax(maxPlus, a[i] + dpCurr[i]);
            setmax(maxMinus, -a[i] + dpCurr[i]);
        }
        std::swap(dpCurr,dpNext);
    }
    std::cout << *std::max_element(all(dpCurr)) << '\n';
}
