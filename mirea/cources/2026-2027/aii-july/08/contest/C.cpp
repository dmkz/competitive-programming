// Нам выгодно всегда удалять подотрезок длины k, так как чем больше элементов мы удалим,
// тем больше будет итоговый минимум массива. Переберём все подотрезки длины k и посчитаем
// ответ, который получится после удаления этого отрезка. Пусть мы хотим удалить отрезок
// [i, i+k-1]. Тогда в массиве останутся префикс [1 .. i-1] и суффикс [i+k .. n]. Чтобы
// быстро считать минимум, нам нужно предподсчитать минимальный элемент на каждом префиксе,
// на каждом суффиксе, а затем брать минимум из pref[i-1] и suff[i+k].
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
const int inf = (int)1e9+7;
void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(1+n+1, inf);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // считаем минимум на префиксе:
    vector<int> pref(1+n+1, inf);
    for (int i = 1; i <= n; i++)
        pref[i] = min(pref[i-1], a[i]);
    // считаем минимум на суффиксе:
    vector<int> suff(1+n+1, inf);
    for (int i = n; i >= 1; i--)
        suff[i] = min(suff[i+1], a[i]);
    // считаем ответ: выгодно всегда удалять подотрезок длины k
    int answ = -inf;
    for (int i = 1; i + k - 1 <= n; i++)
        answ = max(answ, min(pref[i-1], suff[i+k]));
    cout << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
