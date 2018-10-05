/*
    Задача: 835. Задача о рюкзаке
    
    Решение: рекурсивный перебор, O(2^n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

int n, w[20], p[20];
ll curr_mask, curr_p, curr_w, best_mask, best_p, limit;

#define nOnes(x) __builtin_popcountll(x)

void brute(int i) {
    if (curr_w > limit) return;
    if (i == n) {
        if (curr_p > best_p) {
            best_mask = curr_mask;
            best_p = curr_p;
            return;
        }
        if (curr_p < best_p) return;
        int nc = nOnes(curr_mask);
        int nb = nOnes(best_mask);
        if (nc < nb || (nc == nb && curr_mask > best_mask)) {
            best_mask = curr_mask;
            best_p = curr_p;
        }
        return;
    }
    // берем i-го
    curr_w += w[i];
    curr_p += p[i];
    curr_mask |= ll(1) << (n-i);
    brute(i+1);
    curr_w -= w[i];
    curr_p -= p[i];
    curr_mask &= ~(ll(1) << (n-i));
    // не берем i-го
    brute(i+1);
}

int main() {
    scanf("%d %lld", &n, &limit);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &w[i], &p[i]);
    }
    brute(0);
    printf("%d %lld\n", nOnes(best_mask), best_p);
    for (int i = 0; i < n; ++i) {
        if ((best_mask >> (n - i)) & 1) {
            printf("%d ", i+1);
        }
    }
    return 0;
}