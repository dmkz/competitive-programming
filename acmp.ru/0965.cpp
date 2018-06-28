/*
    "Мафия в городе": графы, рекурсивный перебор
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int nVert, nEdges;
    scanf("%d %d", &nVert, &nEdges);
    
    std::vector<int> a(nEdges), b(nEdges);
    
    std::vector<std::vector<int>> edges(1+nVert);
    
    for (int i = 0; i < nEdges; ++i) {
        scanf("%d %d", &a[i], &b[i]);
        if (a[i] > b[i]) std::swap(a[i], b[i]);
        edges[a[i]].push_back(i);
        edges[b[i]].push_back(i);
    }
    
    std::vector<bool> used(nEdges, false);
    
    std::vector<bool> set(1+nVert, false);
    
    int minCount = nVert, nUsed = 0, answer = 1;
    
    std::vector<bool> minSet(1+nVert, true);
    
    std::function<void(int,int)> go = [&](const int curr, const int count) {
        if (nUsed == nEdges) {
            // Пересчитать ответ
            if (count < minCount) {
                minCount = count;
                answer = 1;
                minSet = set;
            } else if (count == minCount) {
                answer++;
            }
            return;
        }
        if (curr > nVert) {
            return;
        }
        // Берем текущую вершину
        for (auto& e : edges[curr]) {
            if (!used[e]) {
                used[e] = true;
                ++nUsed;
            }
        }
        set[curr] = true;
        go(curr+1, count+1);
        
        // Возвращаем все на место и не берем текущую вершину
        set[curr] = false;
        for (auto& e : edges[curr]) {
            if (used[e] && !set[a[e]] && !set[b[e]]) {
                used[e] = false;
                --nUsed;
            }
        }
        go(curr+1, count);
    };
    
    go(1, 0);
    
    printf("%d %d\n", minCount, answer);
    for (int i = 1; i <= nVert; ++i) {
        if (minSet[i]) {
            printf("%d ", i);
        }
    }
    return 0;
}