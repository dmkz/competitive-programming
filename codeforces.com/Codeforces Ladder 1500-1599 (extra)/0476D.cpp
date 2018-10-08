/*
    Problem: 476D. Dreamoon and Sets
    
    Solution: constructive, gcd, O(n log(n))
    
    Auhtor: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <cassert>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<std::vector<int>> answer;
    int p = 1,m = 0;
    while (n--) {
        std::vector<int> temp{p,p+2,p+4};
        if (gcd(p, p+1) == 1 && gcd(p+1,p+2) == 1 && gcd(p+1, p+4) == 1) {
            temp.push_back(p+1);
        } else if (gcd(p, p+3) == 1 && gcd(p+3,p+2) == 1 && gcd(p+3, p+4) == 1) {
            temp.push_back(p+3);
        } else {
            assert(false);
        }
        p += 6;
        for (auto& it : temp) {it *= k; m = std::max(m,it);};
        answer.push_back(temp);
    }
    printf("%d\n", m);
    for (auto& row : answer) {
        for (auto& it : row) {
            printf("%d ", it);
        }
        printf("\n");
    }
    return 0;
}