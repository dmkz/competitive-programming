#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define int int64_t
// быстрое возведение в степень:
int binpow(int a, int n, int mod) {
    int res = 1 % mod;
    while (n > 0) {
        if (n % 2 == 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int removeMultiplier(int &x, int p) {
// удаляем из `x` все множители `p` и возвращаем то, сколько было удалено
    int nRemoves = 0;
    while (x > 0 && x % p == 0) {
        x /= p;
        nRemoves++;
    }
    return nRemoves;
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем элементы массивов `a` и `b` и считаем, сколько каждого элемента (count)
    // также для каждого значения x должны посчитать сколько одинаковых пар (x, i) 
    // в массивах `a` и `b`. Пример: a = {1,2,3,4}, b = {1,2,3,4}. Ответ: 1 способ
    // count = {{1,2}, {2,2}, {3,2}, {4,2}}, repeats = {{1,2}, {2,2}, {3,2}, {4,2}}
    int n; std::cin >> n;
    std::vector<int> a(n), b(n);
    std::map<int, int> count, repeats;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        count[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        count[b[i]]++;
        repeats[b[i]] += (a[i] == b[i]); // пары (a[i], i) равны (b[i], i)
    }
    int m; std::cin >> m;
    
    // так как делить на 2 не можем по непростому модулю, то
    // придётся выносить все двойки из факториалов, удалять нужное количество двоек,
    // и умножать на оставшиеся двойки!!! (гемор)
    
    // считаем факториалы без двоек (вообще) и сколько раз каждый делится на 2:
    std::vector<int> factWithout2(2 * n + 1, 1), factCnt2(2 * n + 1, 0);
    for (int i = 1; i < isz(factWithout2); i++) {
        int x = i;
        int cnt2 = removeMultiplier(x, 2);
        factWithout2[i] = factWithout2[i-1] * x % m;
        factCnt2[i] = factCnt2[i-1] + cnt2;
    }
    // считаем ответ:
    int answ = 1;
    for (const auto &[x, cnt] : count) {
        // В обычной ситуации:
        // `cnt` одинаковых элементов `x` мы сможем переставить `cnt!` способами
        // В нашей ситуации у нас могут быть одинаковые пары `(x, i)` в массивах
        // `a` и `b` одновременно. Они считаются одинаковыми, поэтому мы должны
        // поделить на `2` для каждой такой пары. Делить мы не можем, так как
        // модуль может не быть простым, поэтому удаляем все двойки из факториала
        // (числителя дроби) и потом домножим на нужное количество двоек
        int curr = factWithout2[cnt] * binpow(2, factCnt2[cnt] - repeats[x], m) % m; 
        (answ *= curr) %= m;
    }
    std::cout << answ << std::endl;
}