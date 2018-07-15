/*
    "Производство деталей": графы, поиск в глубину, O(n)
*/

#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

int main() {
    int n; scanf("%d", &n);
    
    std::vector<int> time(n);
    for (auto& it : time) {
        scanf("%d", &it);
    }
    
    std::vector<std::vector<int>> next(n);
    for (int i = 0; i < n; ++i) {
        int k; scanf("%d", &k);
        while (k--) {
            int vert; scanf("%d", &vert); --vert;
            next[i].push_back(vert);
        }
    }
    
    std::vector<bool> visited(n, false);
    
    std::vector<int> answ;

    std::function<void(int)> visit = [&](const int curr) {
        for (auto vert : next[curr]) {
            if (!visited[vert]) {
                visited[vert] = true;
                visit(vert);
            }
        }
        answ.push_back(curr);        
    };
    
    visited[0] = true;
    visit(0);
    long long sum = 0;
    for (auto& it : answ) {
        sum += time[it];
    }
    printf("%s %d\n", std::to_string(sum).c_str(), (int)answ.size());
    for (auto& it : answ) {
        printf("%d ", it+1);
    }
    return 0;
}