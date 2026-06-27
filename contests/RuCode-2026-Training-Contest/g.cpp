// sparse table, XOR, перестановки, O(n log(n) + q * log(n)^2)
// Задача: G, Вердикт: ОК, Время: 143ms, Память: 34.16Mb
#include <bits/stdc++.h>
const int PMAX = 19, NMAX = (1 << 18);
using pii = std::pair<int,int>;
pii st[PMAX][NMAX];

pii f(pii a, pii b) {
    return {std::min(a.first, b.first),
            std::max(a.second, b.second)};
}

pii query(int l, int r, int x) {
// мин/макс на отрезке после КСОР-применения x к L и R
    pii result{INT_MAX, INT_MIN};
    while (l <= r) {
        // найти хвост из нулей
        int k = 0;
        while (l + (1 << (k+1)) - 1 <= r && // выход за пределы отрезка
               (l & ((1 << (k+1)) - 1)) == 0 // на конце k+1 нулей
        )
            k++;
        // найти границы очередного отрезка
        int li = (l ^ x) & ~((1 << k) - 1);
        result = f(result, st[k][li]);
        l += (1 << k);
    }
    return result;
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    for (int i = 0, ai; i < n; i++) {
        std::cin >> ai;
        st[0][ai] = {i, i};
    }
    // построение спарс таблицы:
    for (int p = 1; p < PMAX; p++)
        for (int i = 0; i + (1 << p) - 1 < n; i++)
            st[p][i] = f(st[p-1][i], st[p-1][i+(1<<(p-1))]);
    // ответ на запросы:
    int x = 0;
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int xi; std::cin >> xi;
            x ^= xi;
        } else {
            int L, R; std::cin >> L >> R;
            auto [min, max] = query(L, R, x);
            std::cout << max - min + 1 << "\n";
        }
    }
}
