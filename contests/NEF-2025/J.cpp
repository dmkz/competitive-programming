// формула Байеса, жадные алгоритмы, динамическое программирование
/*
    Test case #1:
    2 2
    70 30
    
    x -> 0.7 * 2 * x = 1.4^2 * x * 0.5
    x -> 0.3 * 2 * x = 0.6^2 * x * 0.5
    
    1000 * ((1.4^2 - 1) * 0.5 + (0.6^2 - 1) * 0.5) = 160 <- Тест #1
    
    Test case #2:
    2 30
    30 70
    
    1000 * ((1.4^30 - 1) * 0.5 + (0.6^30 - 1) * 0.5) = 12099716.17785
    
    Test case #5:
    1 5
    61
    
    1000 * (1.22^5 - 1) = 1702.7081632
    
    Формула:
    
    1000 * sum_{i=1}^n ((2 * p)^k - 1) * Prob(i)
    
    Prob(i) = 1 / n
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using ld = long double;
using vd = vector<ld>;
using pdi = pair<ld, int>;
using vpdi = vector<pdi>;
using pii = pair<int,int>;
using vi = vector<int>;
ld normalize(vd &vec) {
// считает сумму элементов вектора + делит каждый элемент на сумму
    ld sum = accumulate(all(vec), ld(0));
    for (auto &it : vec) it /= sum;
    return sum;
}
main() {
    for (int n, k; std::cin >> n >> k; ) {
        // читаем + сжимаем вероятности (так как значения 0 ... 100)
        vpdi p = [&](){
            vi cnt(101);
            for (int i = 0, pi; i < n; i++) {
                cin >> pi;
                cnt[pi]++;
            }
            vpdi res;
            for (int pi = 0; pi <= 100; pi++)
                if (cnt[pi] > 0)
                    res.emplace_back(pi / ld(100), cnt[pi]);
            return res;
        }();
        int initN = n;
        n = isz(p);
        // предподсчитываем вероятности по формуле Байеса:
        vector ph(k+1, vector(k+1, vd(n)));
        vector prob(k+1, vector(k+1, ld(0)));
        for (int W = 0; W <= k; W++)
            for (int L = 0; W + L <= k; L++) {
                for (int i = 0; i < n; i++) {
                    auto [pi, ci] = p[i];
                    ph[W][L][i] = pow(pi, W) * pow(1 - pi, L) * ci / initN;
                }
                prob[W][L] = normalize(ph[W][L]);
            }
        // решаем задачку:
        auto goBreakingBad = [&](int W, int L) -> ld {
            // идём во все тяжкие при W выигрышах и L проигрышах:
            // 1000 * sum_{i=1}^n ((2 * p)^k - 1) * Prob(i)
            ld res = 0;
            for (int i = 0; i < n; i++) {
                auto [pi, _] = p[i];
                res += (pow(2 * pi, k - W - L) - 1) * ph[W][L][i];
            }
            return 1000 * res * prob[W][L];
        };
        // запускаем оптимальную стратегию игры:
        map<pii, ld> cache;
        function<ld(int,int)> solve = [&](int W, int L) -> ld {
            if (W + L == k) return 0;
            pii state(W, L);
            if (auto it = cache.find(state); it != cache.end())
                return it->second;
            ld res = max<ld>({goBreakingBad(W, L), 0,
                              solve(W+1, L) + solve(W, L+1)});
            return cache[state] = res;
        };
        cout << fixed << setprecision(12);
        cout << solve(0, 0) << endl;
    }
    
}
