#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем исходные данные:
    int n, minLen;
    cin >> n >> minLen;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // строим префикс-суммы:
    vector<int> pref_sum_a(n+1);
    for (int i = 0; i < n; i++)
        pref_sum_a[i+1] = pref_sum_a[i] + a[i];
    // считаем максимальный ответ:
    double maxAnsw = 0;
    for (int L = 0; L < n; L++) {
        for (int R = L+minLen-1; R < n; R++) {
            double p = pref_sum_a[R+1] - pref_sum_a[L];
            double q = R - L + 1;
            maxAnsw = max(maxAnsw, p / q);
        }
    }
    // выводим ответ в фиксированной форме с 20 знаками после запятой:
    cout << setprecision(20) << fixed;
    cout << maxAnsw << endl;
}