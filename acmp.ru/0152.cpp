/*
    Задача: 152. Построение
    
    Решение: жадный алгоритм, графы, O(n^3)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>

int main() {
    int n, m; scanf("%d %d", &n, &m);
    std::vector<std::vector<int>> compare(n, std::vector<int>(n));
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a,--b;
        if (compare[a][b] == -1 || a == b) {
            printf("No\n");
            return 0;
        }
        compare[a][b] =  1;
        compare[b][a] = -1;
    }
    std::vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        // Поиск вершины, больше которой никого нет, из множества оставшихся вершин
        int res = -1;
        for (int u = 0; u < n; ++u) {
            if (visited[u]) continue;
            bool flag = true;
            for (int v = 0; v < n; ++v) {
                if (compare[u][v] == -1) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                res = u;
                break;
            }
        }
        if (res == -1) {
            printf("No\n");
            return 0;
        }
        visited[res] = true;
        for (int v = 0; v < n; ++v) {
            compare[res][v] = compare[v][res] = 0;
        }
    }
    printf("Yes\n");
    return 0;
}