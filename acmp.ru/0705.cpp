/*
    Задача: 705. Оценка
    
    Решение: динамическое программирование, рекурсия, O(log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

struct Record {
    int x, s0, s1, s2;
};

Record fast(int x, int n, int mod) {
    if (n == 1) {
        return Record{x % mod, 1 % mod, 0, 0};
    } else if (n % 2 == 1) {
        auto prev = fast(x, n - 1, mod);
        n /= 2;
        Record curr;
        curr.s2 = int((prev.s2 + 4LL * n * n % mod * prev.x) % mod);
        curr.s1 = int((prev.s1 + 2LL * n * prev.x) % mod);
        curr.s0 = int((prev.x + prev.s0) % mod);
        curr.x = int(1LL * prev.x * x % mod);
        return curr;
    } else {
        auto prev = fast(x, n / 2, mod);
        n /= 2;
        Record curr;
        curr.x = int(1LL * prev.x * prev.x % mod);
        curr.s0 = int((prev.s0 + 1LL * prev.s0 * prev.x) % mod);
        curr.s1 = int((prev.s1 + (prev.s1 + 1LL * n * prev.s0) % mod * prev.x) % mod);
        curr.s2 = int((prev.s2 + (prev.s2 + 2LL * n * prev.s1 + 1LL * n * n % mod * prev.s0) % mod * prev.x) % mod);
        return curr;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n, mod;
    while (std::cin >> n >> mod) { std::cout << fast(2, n, mod).s2 << std::endl; }
    return 0;
}