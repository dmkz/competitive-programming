#include <bits/stdc++.h>
using tiii = std::tuple<int,int,int>;
// visited[предыщущий шаг][строка][столбец] = была ли посещена клетка
int visited[2][500][500];
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    int dr[2], dc[2];
    for (int i = 0; i < 2; i++)
        std::cin >> dr[i] >> dc[i];
    // запускаем поиск в ширину, чередуя шаг и отмечая посещённые точки:
    std::queue<tiii> q;
    q.push({0,0,0});
    q.push({1,0,0});
    visited[0][0][0] = 1;
    visited[1][0][0] = 1;
    while (q.size()) {
        auto [dir, r, c] = q.front();
        q.pop();
        int deltaR = dr[1-dir];
        int deltaC = dc[1-dir];
        for (int rot = 0; rot < 2; rot++) {
            for (int signR : {-1, 1})
                for (int signC : {-1, 1}) {
                    int nr = r + signR * deltaR;
                    int nc = c + signC * deltaC;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[1-dir][nr][nc])
                        continue;
                    q.push({1-dir,nr,nc});
                    visited[1-dir][nr][nc] = 1;
                }
            std::swap(deltaR, deltaC);
        }
    }
    // выводим ответ:
    int answ = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            answ += (visited[0][r][c] || visited[1][r][c]);
    std::cout << answ << std::endl;
}
