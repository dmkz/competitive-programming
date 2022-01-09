#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using Real = double;
int main() {
    // чтение графа + сортировка вероятностей:
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n,k,s;
    std::cin >> n >> k >> s;
    std::vector<int> totalCnt(1+n);
    std::vector<std::vector<int>> cnt(1+n, std::vector<int>(1+n));
    std::vector<std::vector<Real>> probabilities(1+n);
    for (int i = 1; i <= n; i++) {
        totalCnt[i] = 0;
        for (int j = 1; j <= n; j++) {
            std::cin >> cnt[i][j];
            totalCnt[i] += cnt[i][j];
        }
        int q; std::cin >> q;
        for (int j = 0; j < totalCnt[i]; j++) {
            int p; std::cin >> p;
            probabilities[i].push_back(p * 1.0 / q);
        }
        std::sort(all(probabilities[i]),std::greater<>());
    }
    // начинаем считать динамику:
    std::vector<std::vector<Real>> dp(1+k,std::vector<Real>(1+n));
    dp[0][s]=1;
    for (int step = 1; step <= k; step++) {
        // нужно посортировать с предыдущего слоя в порядке убывания вероятностей:
        std::vector<std::pair<Real,int>> edges;
        for (int to = 1; to <= n; to++) {
            edges.emplace_back(dp[step-1][to],to);
        }
        std::sort(all(edges),std::greater<>());
        for (int from = 1; from <= n; from++) {
            // смотрим, куда можем пойти из from
            // получаем список из вершин to
            // сортируем этот список по dp[step-1][to]
            // сопоставляем максимуму максимум и т.д.
            // записываем скалярное произведение
            // в dp[step][from]
            int ip = 0;
            Real res = 0;
            for (auto &[prob,to] : edges) {
                for (int j = 0; j < cnt[from][to]; j++) {
                    res += prob * probabilities[from][ip++];
                }
            }
            dp[step][from] = res;
        }
    }
    std::cout << std::setprecision(12) << std::fixed << dp[k][1] << std::endl;
    return 0;
}