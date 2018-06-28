/*
    "Мусорщик": динамическое программирование
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cmath>

int main() {
    int n;
    scanf("%d", &n);
    
    const int INF = (int)1e9;
    std::vector<int> min, max;
    for (int i = 0; i < n; ++i) {
        int r, c;
        scanf("%d %d", &c, &r);
        while ((int)min.size() <= r) min.push_back( INF);
        while ((int)max.size() <= r) max.push_back(-INF);
        min[r] = std::min(min[r], c);
        max[r] = std::max(max[r], c);
    }
    
    std::vector<std::vector<int>> dist(2, std::vector<int>(min.size(), -1));
    // Инициализация:
    max[1] = std::max(max[1], 1);
    min[1] = std::min(min[1], 1);
    dist[0][1] = max[1]-1 + max[1]-min[1];
    dist[1][1] = max[1]-1;
    // Переходы:
    for (int curr = 2, prev = 1; curr < (int)min.size(); ++curr) {
        while (min[curr] == INF) ++curr;
        // Если последняя посещенная клетка на текущей строке - минимум
        dist[0][curr] = std::min(
            dist[0][prev]+std::abs(max[curr]-min[prev]),
            dist[1][prev]+std::abs(max[curr]-max[prev])
        )+curr-prev+max[curr]-min[curr];
        
        // Если последняя посещенная клетка на текущей строке - максимум
        dist[1][curr] = std::min(
            dist[0][prev]+std::abs(min[curr]-min[prev]),
            dist[1][prev]+std::abs(min[curr]-max[prev])
        )+curr-prev+max[curr]-min[curr];
        // Переход к следующей итерации:
        prev = curr;
    }    
    
    printf("%d", std::min(dist[0].back(), dist[1].back()));
    return 0;
}