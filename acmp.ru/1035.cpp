/*
    "Кондиционеры": динамическое программирование, O(n+m+maxW)
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> count(1+1000, 0);
    for (int i = 0; i < n; ++i) {
        int value; scanf("%d", &value);
        count[value]++;
    }
    
    std::vector<int> min(1+1000, (int)1e9);
    int m; scanf("%d", &m);
    while (m--) {
        int value, cost; 
        scanf("%d %d", &value, &cost);
        min[value] = std::min(min[value], cost);
    }
    
    std::vector<int> suff(1+1000, (int)1e9);
    suff[1000] = min[1000];
    for (int i = 999; i >= 0; --i) {
        suff[i] = std::min(suff[i+1], min[i]);
    }
    
    int sum = 0;
    for (int i = 0; i <= 1000; ++i) {
        sum += count[i] * suff[i];
    }
    printf("%d", sum);
    
    return 0;
}