#include <stdio.h>
#include <algorithm>
#include <vector>

struct Pair {
    int count, cost;
};

int main() {
    int need, m;
    scanf("%d %d", &need, &m);
    
    std::vector<Pair> pairs;
    while (m--) {
        int count, cost;
        scanf("%d %d", &count, &cost);
        pairs.push_back(Pair{count,cost});
    }
    const int INF = 1e9;
    std::vector<int> min(1+need, INF); // min[count]
    min[0] = 0;
    for (int i = 1; i <= need; ++i) {
        for (auto& p : pairs) {
            min[i] = std::min(min[i], min[std::max(0, i-p.count)]+p.cost);
        }
    }
    printf("%d", min[need]);
    return 0;
}