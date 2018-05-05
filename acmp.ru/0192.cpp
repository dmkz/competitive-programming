#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    int n; scanf("%d", &n); 
    
    std::vector<int> a(n); 
    for (auto& it : a) scanf("%d", &it);
    
    if (!std::next_permutation(a.begin(), a.end())) {
        std::reverse(a.begin(), a.end());
    }
    
    for (auto& it : a) {
        printf("%d ", it);
    }
    printf("\n");
    
    return 0;
}