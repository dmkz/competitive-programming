/*
    "Интересная игра c числами": сортировка, жадный алгоритм, O(n log(n))
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

struct Pair {
    int a, b;
};

int main() {
    int n;
    scanf("%d", &n);
     
    std::vector<Pair> pairs(n);
    for (auto& it : pairs) {
        scanf("%d %d", &it.a, &it.b);
    }
    
    std::stable_sort(pairs.begin(), pairs.end(), [](const Pair& lhs, const Pair& rhs) {
        return lhs.a + lhs.b > rhs.a + rhs.b;
    });

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += (i % 2 == 0) ? (pairs[i].a) : (-pairs[i].b);
    }
    std::cout << sum;
    return 0;
}