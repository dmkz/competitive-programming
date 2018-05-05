#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    int n; scanf("%d", &n);
    std::vector<std::vector<int>> c(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &c[i][j]);
        }
    }
    std::vector<int> perm(n); for (int i = 0; i < n; ++i) perm[i] = i;
    
    std::function<int()> cur_sum = [&]() {
        int answ = 0;
        for (int i = 0; i < n; ++i) {
            answ += c[i][perm[i]];
        }
        return answ;
    };
    int min_sum = (int)1e9+1;
    do {
        min_sum = std::min(min_sum, cur_sum());
    } while (std::next_permutation(perm.begin(), perm.end()));
    printf("%d\n", min_sum);        
    return 0;
}