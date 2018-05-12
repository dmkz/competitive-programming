#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

struct Point { int row, col; };

int main() {
    // Чтение данных
    int n; scanf("%d", &n); 
    std::vector<std::vector<int>> item(n, std::vector<int>(n));
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            scanf("%d", &item[row][col]);
        }
    }
    // Замена всех ненулевых элементов их номерами по-порядку и добавление их в очередь
    const int INF = (int)1e9+1;
    std::vector<int> values{0};
    std::queue<Point> queue;
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (item[row][col] != 0) {
                values.push_back(item[row][col]);
                item[row][col] = (int)values.size()-1;
                queue.push({row, col});
                dist[row][col] = 0;
            }
        }
    }
    // Поиск в ширину
    while (!queue.empty()) {
        int row = queue.front().row;
        int col = queue.front().col;
        queue.pop();
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc == 1) {
                    int nr = dr + row;
                    int nc = dc + col;
                    if (!(0 <= nr && nr < n && 0 <= nc && nc < n)) continue;
                    if (dist[nr][nc] > dist[row][col] + 1) {
                        item[nr][nc] = item[row][col];
                        dist[nr][nc] = dist[row][col] + 1;
                        queue.push({nr, nc});
                    } else if (dist[nr][nc] == dist[row][col]+1) {
                        // Достижима из двух точек
                        if (item[nr][nc] != item[row][col]) {
                            item[nr][nc] = 0;
                        }
                    }
                }
            }
        }
    }
    char buf[100000];
    for (int row = 0; row < n; ++row) {
        int size = 0;
        for (int col = 0; col < n; ++col) {
            auto& it = item[row][col];
            size += sprintf(buf+size, "%d ", values[it]);
            assert(buf[size] == '\0');
        }
        printf("%s\n", buf);
    }
    return 0;
}