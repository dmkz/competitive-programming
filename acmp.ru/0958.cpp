// двумерное динамическое программирование, O(n^2 * m)
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m; std::cin >> n >> m;
    // читаем матрицу смежности
    std::vector<std::string> g(n);
    for (auto &it : g)
        std::cin >> it;
    std::vector<int> prevPath, currPath, nextPath;
    for (int id = 0; id < m; id++) {
        prevPath = currPath;
        currPath.clear();
        // читаем текущий путь
        do {
            int v; std::cin >> v; v--;
            currPath.push_back(v);
        } while (currPath.back() != n-1);
        // сливаем два пути: предыдущий и текущий
        if (prevPath.size()) {
            // dp[i][j][last] = можно ли собрать путь из:
            // 1) префикса длины i предыдущего пути
            // 2) суффикса длины j текущего пути
            // 3) чтобы на конце стояла вершина из пути "last":
            //    0 = prev, 1 = curr
            std::vector dp(isz(prevPath), std::vector(isz(currPath), std::vector(2, std::make_pair(false, -1))));
            dp[0][0][0] = {true, -1};
            dp[0][0][1] = {true, -1};
            for (int i = 0; i < isz(prevPath); i++) {
                for (int j = 0; j < isz(currPath); j++) {
                    // можем ли мы поставить i-й элемент в конец пути?
                    if (i > 0) {
                        int x = prevPath[i];
                        int a = prevPath[i-1], b = currPath[j];
                        if (dp[i-1][j][0].first && g[a][x] == '-')
                            dp[i][j][0] = {true, 0};
                        if (dp[i-1][j][1].first && g[b][x] == '-')
                            dp[i][j][0] = {true, 1};
                    }
                    // можем ли мы поставить j-й элемент в конец пути?
                    if (j > 0) {
                        int x = currPath[j];
                        int a = prevPath[i], b = currPath[j-1];
                        if (dp[i][j-1][0].first && g[a][x] == '-')
                            dp[i][j][1] = {true, 0};
                        if (dp[i][j-1][1].first && g[b][x] == '-')
                            dp[i][j][1] = {true, 1};
                    }
                }
            }
            // восстанавливаем ответ:
            int lastI = isz(prevPath)-1, lastJ = isz(currPath)-2;
            int place = 0;
            if (dp[lastI][lastJ][place].first) {
                nextPath.clear();
                while (place != -1) {
                    auto [flag, step] = dp[lastI][lastJ][place];
                    if (place == 0) {
                        nextPath.push_back(prevPath[lastI]);
                        lastI--;
                    } else {
                        nextPath.push_back(currPath[lastJ]);
                        lastJ--;
                    }
                    place = step;
                }
                std::reverse(all(nextPath));
            } else {
                std::cout << "-1" << std::endl;
                return 0;
            }
            currPath = nextPath;
            nextPath.clear();
        }
    }
    for (auto it : currPath)
        std::cout << it+1 << ' ';
    std::cout << std::endl;
}
