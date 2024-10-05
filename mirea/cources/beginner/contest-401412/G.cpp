#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходные данные:
    int n, maxIncrease, maxNumOps;
    cin >> n >> maxIncrease >> maxNumOps;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // Сортируем героев. Удалять будем самых слабых (т.е. некоторый префикс)
    sort(a.begin(), a.end());
    // считаем суффикс-суммы сил героев:
    // suff[i] = a[i] + a[i+1] + ... + a[n-1];
    // суффикс-суммы нужны для того, чтобы говорить сумму тех героев,
    // которых не выкинули (выкидываем ведь префикс)
    vector<int64_t> suff(n);
    suff[n-1] = a[n-1];
    for (int i = n-2; i >= 0; i--)
        suff[i] = suff[i+1] + a[i];
    // теперь перебираем то, сколько мы выкинем, и для каждого такого значения
    // находим ответ. считаем максимум среди всех
    double bestAnsw = 0;
    for (int64_t nRemove = 0; nRemove < n && nRemove <= maxNumOps; nRemove++) {
        int64_t nUsed = n - nRemove; // сколько чуваков осталось
        double sum = suff[nRemove]; // сумма сил оставшихся
        // теперь не важно, кого из оставшихся увеличивать, так как всё равно
        // числитель увеличится на +1 от любого увеличения
        // каждого мы можем увеличить не больше, чем на `maxIncrease`
        // суммарно всех мы можем увеличить не больше, чем на `nUsed` * `maxIncrease`
        // ну и мы уже потратили `nRemove` операций из `maxNumOps` дозволенных
        double p = sum + min(maxNumOps - nRemove, maxIncrease * nUsed);
        double q = nUsed;
        bestAnsw = max(bestAnsw, p / q);
    }
    // выводим ответ:
    cout << fixed << setprecision(20);
    cout << bestAnsw << endl;
}