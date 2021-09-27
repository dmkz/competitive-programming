// Решение: динамическое программирование, теория игр, ретроспективный анализ, O(t*n*m)
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129987891
// от текущего хода и координат клетки зависит, выиграем мы или програем
// то есть, состояние (step, row, col) -> win or lose
// будем считать динамику вида победит ли игрок, оказавшийся в этом состоянии
// он победит, если есть хотя бы один переход в такое состояние, в котором победы нет
// то есть передаст очередь хода в заведомо проигрышное состояние
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("fma")
#include <bits/stdc++.h>
const int steps[] = {2,3,5};
std::vector<std::vector<bool>> win[3];
bool solve(int n, int m) {
    for (int stepId = 0; stepId < 3; stepId++) {
        win[stepId].assign(n,std::vector<bool>(m,false));
    }
    // считаем динамику:
    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            for (int stepId = 0; stepId < 3; stepId++) {
                int step = steps[stepId];
                // смотрим шаг вниз:
                if (i+step < n && !win[(stepId+1)%3][i+step][j]) {
                    win[stepId][i][j] = true;
                }
                // смотрим шаг вправо:
                if (j+step < m && !win[(stepId+1)%3][i][j+step]) {
                    win[stepId][i][j] = true;
                }
            }
        }
    }
    return win[0][0][0];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::map<std::pair<int,int>,bool> cache; // будем кэшировать запросы чтобы не отвечать
                                             // на одни и те же несколько раз
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int n, m; std::cin >> n >> m;
        if (n > m) std::swap(n,m);
        // смотрим считали ли уже ответ:
        auto it = cache.find({n,m});
        if (it == cache.end()) {
            // нет, не считали - считаем + кэшируем
            it = cache.insert({{n,m},solve(n,m)}).first;
        }
        // выводим ответ
        std::cout << (it->second ? "Alice" : "Bob") << "\n";
    }
}