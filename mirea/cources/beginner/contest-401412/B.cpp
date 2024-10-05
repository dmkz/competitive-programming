#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем данные:
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // считаем префикс-суммы:
    vector<int> pref_sum_1(n+1);
    for (int i = 0; i < n; i++) {
        pref_sum_1[i+1] = pref_sum_1[i] + a[i];
    }
    // функция для того, чтобы узнать количество 0 и 1 на отрезке [L,R]:
    auto count1 = [&](int L, int R) {
        if (L > R) return 0;
        assert(0 <= L && L <= R && R < n);
        return pref_sum_1[R+1] - pref_sum_1[L];
    };
    auto count0 = [&](int L, int R) {
        if (L > R) return 0;
        assert(0 <= L && L <= R && R < n);
        return R - L + 1 - count1(L, R);
    };
    // считаем ответ: переберём отрезок, который переворачиваем, и смотрим
    // сколько единиц получится
    int bestAnsw = 0;
    for (int L = 0; L < n; L++) {
        for (int R = L; R < n; R++) {
            int currAnsw = count1(0, L-1) + count0(L, R) + count1(R+1, n-1);
            if (bestAnsw < currAnsw)
                bestAnsw = currAnsw;
        }
    }
    cout << bestAnsw << endl;
}