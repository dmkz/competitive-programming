// игры, жадные алгоритмы, очередь с приоритетами
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
void solve() {
// Жадная стратегия: на своём ходу игрок каждый раз использует максимальный элемент
// против максимального элемента противника, чтобы уменьшить его как можно сильнее
    int n, m; std::cin >> n >> m;
    std::priority_queue<int> qa, qb;
    for (int i = 0, ai; i < n; i++) {
        std::cin >> ai;
        qa.push(ai);
    }
    for (int i = 0, bi; i < m; i++) {
        std::cin >> bi;
        qb.push(bi);
    }
    for (int moves = 0; isz(qa) && isz(qb); moves++) {
        if (moves % 2 == 0) {
            // Ход Алисы:
            int x = qa.top();
            int y = qb.top(); qb.pop();
            y -= x;
            if (y > 0)
                qb.push(y);
        } else {
            // Хоб Боба:
            int x = qb.top();
            int y = qa.top(); qa.pop();
            y -= x;
            if (y > 0)
                qa.push(y);
        }
    }
    std::cout << (isz(qa) > 0 ? "Alice" : "Bob") << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
