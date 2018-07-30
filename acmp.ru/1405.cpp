/*
    Задача: 1405. Лягушка
    
    Решение: Sparse Table, O((n+q)*log(MAX))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <functional>

inline int mod(int a, int MOD) {
    return a >= 0 ? a % MOD : MOD - (-a) % MOD;
}

inline int add(int a, int b, int MOD) {
    return (a += b) >= MOD ? a - MOD : a;
}

inline int sub(int a, int b, int MOD) {
    return (a -= b) < 0 ? a + MOD : a;
}

int main() {
    int n; scanf("%d", &n);
    
    std::vector<int> a(n);
    for (auto& it : a) {
        scanf("%d", &it);
        it = mod(it, n);
    }
    
    static int jump[2][32][200000]; // [inverse][pow][pos] --> jump
    
    for (int i = 0; i < n; ++i) {
        jump[0][0][i] = add(i, a[i], n);
        jump[1][0][i] = sub(i, a[i], n);
    }
    
    for (int pow = 1; pow < 32; ++pow) {
        for (int i = 0, next; i < n; ++i) {
            next = jump[0][pow-1][i];
            jump[0][pow][i] = jump[1][pow-1][next];
            
            next = jump[1][pow-1][i];
            jump[1][pow][i] = jump[0][pow-1][next];
        }
    }
    
    std::function<int(int,int)> query = [&](int p, int nSteps) {
        for (int pow = 31, inv = 0; pow >= 0; --pow) {
            if ((nSteps >> pow) & 1) {
                p = jump[inv][pow][p];
                inv = 1 - inv;
            }
        }
        return p;
    };
    
    int nQueries; scanf("%d", &nQueries);
    while (nQueries--) {
        int pos, nSteps;
        scanf("%d %d", &pos, &nSteps);
        printf("%d\n", query(pos, nSteps));
    }
    return 0;
}