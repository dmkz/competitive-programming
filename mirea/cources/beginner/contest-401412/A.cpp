#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем данные:
    string s;
    cin >> s;
    // считаем, сколько букв A и B на каждом префиксе:
    int n = (int)s.size();
    vector<int> pref_sum_a(n+1);
    for (int i = 0; i < n; i++) {
        pref_sum_a[i+1] = pref_sum_a[i] + (s[i] == 'a');
    }
    // функции для того, чтобы узнать сколько букв a и b на отрезке [L,R]:
    auto countA = [&](int L, int R) {
        if (L > R) return 0;
        assert(0 <= L && L <= R && R < n);
        return pref_sum_a[R+1] - pref_sum_a[L];
    };
    auto countB = [&](int L, int R) {
        if (L > R) return 0;
        assert(0 <= L && L <= R && R < n);
        return R - L + 1 - countA(L, R);
    };
    // считаем ответ. делим ответ на три группы символов:
    // группа из букв A длины len1
    // группа из букв B длины len2
    // оставшаяся группа из букв A
    // Остаётся только перебрать len1 и len2:
    int bestAnsw = 0;
    for (int len1 = 0; len1 <= n; len1++) {
        for (int len2 = 0; len1 + len2 <= n; len2++) {
            int currAnsw = countA(0, len1-1) + countB(len1, len1+len2-1) + countA(len1+len2, n-1);
            if (bestAnsw < currAnsw)
                bestAnsw = currAnsw;
        }
    }
    cout << bestAnsw << endl;
}