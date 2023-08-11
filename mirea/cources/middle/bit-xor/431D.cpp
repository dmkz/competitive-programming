#include <bits/stdc++.h>

typedef long long ll;

const ll INF = (ll)1e18L+10;

ll C[64][64];

void precalc() {
    C[0][0] = 1;
    for (int n = 1; n < 64; ++n) {
        for (int k = 0; k <= n; ++k) {
            C[n][k] = std::min(INF, C[n-1][k] + (k == 0 ? 0 : C[n-1][k-1]));
        }
    }
}

ll count(ll limit, int numOnes) {
    // сколько чисел на отрезке [0, limit] имеют numOnes единичных битов?
    // будем считать комбинаторно
    ll answ = 0;
    for (int bit = 60; numOnes >= 0 && bit >= 0; --bit) {
        if ((limit >> bit) & 1) {
            // текущий бит равен 1
            // тогда до него есть отрезок [0, mid], на котором бит равен 0
            // среди них можем комбинаторно посчитать, сколько чисел имеют заданное
            // число единиц
            answ = std::min(INF, answ + C[bit][numOnes]);
            // теперь осталось посчитать только такие числа, у которых в текущем
            // разряде стоит 1, то есть уже на одну единицу меньше
            numOnes--;
        }
    }
    return answ;
}

ll solve(ll need, int numOnes) {
    ll low = 0, high = (ll)1e18L+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        ll cnt = count(2*mid, numOnes)-count(mid, numOnes);
        if (need <= cnt) high = mid;
        else low = mid;
    }
    return high;
}

int main() {
    precalc();
    ll need; int numOnes;
    while (std::cin >> need >> numOnes)
        std::cout << solve(need, numOnes) << std::endl;
    return 0;
}
