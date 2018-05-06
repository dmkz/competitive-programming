#include <bits/stdc++.h>

typedef int64_t Int;

const int INF = (int)1e9+1;

int main() {
    int n; std::cin >> n;
    
    std::vector<Int> a(n); for (auto& it : a) std::cin >> it;
    
    // Построим граф из вершин - индексов чисел в массиве a:
    std::vector<std::vector<bool>> g(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            auto s = a[i], t = a[j];
            if (t * 3 == s || s * 2 == t) {
                g[i][j] = true;
            }
        }
    }
    
    // Расстояние от выбранной вершины до всех остальных:
    std::vector<int> dist;
    // Поиск в глубину от выбранной вершины:
    std::function<void(int)> dfs = [&](int s) {
        for (int t = 0; t < n; ++t) {
            if (g[s][t] && dist[t] == INF) {
                dist[t] = dist[s]+1;
                dfs(t);
            }
        }
        if (dist[s] == n-1) { // Нашли ответ - выведем его:
            std::vector<int> answ{s};
            while (dist[s] != 0) {
                for (int i = 0; i < n; ++i) {
                    if (dist[s] == dist[i]+1) {
                        answ.push_back(i);
                        s = i;
                        break;
                    }
                }
            }
            std::reverse(answ.begin(), answ.end());
            for (auto& it : answ) {
                std::cout << a[it] << " ";
            }
            std::cout << std::endl;
            std::exit(0);
        }
        dist[s] = INF;
    };
    // Запуск серии поисков в глубину для нахождения ответа:
    for (int i = 0; i < n; ++i) {
        dist.assign(n, INF);
        dist[i] = 0;
        dfs(i);
    }
    throw 1;
}