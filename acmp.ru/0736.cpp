/*
    "Удаление": математика, оптимизация вычислений, O(q*sqrt(n))
*/

#include <stdio.h>
#include <algorithm>
#include <cassert>

inline int solve(int n, int k, int a) {
// Работает за O(sqrt(n))

    const int answ = n;
    while (a >= k && a % k != 0) {
        // Оптимальный параметр для n / k:
        int x = n / k;
        int t1 = (n - x * k + x - 1) / x;
        
        // Оптимальный параметр для a / k:
        int y = a / k;
        int t2 = (a - y * k + y - 1) / y;
        
        // Минимум из оптимальных параметров:
        int t = std::max(1, std::min(t1, t2));
        
        // Переход к следующей итерации:
        n -= t * x;
        a -= t * y;
    }
    return answ - n + a / k;
}
 
int main() {
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    
    while (q--) {
        int item;
        scanf("%d", &item);
        printf("%d\n", solve(n, k, item));
    }

     
    return 0;
}