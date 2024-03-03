#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
void solve() {
    // прочитаем массив, добавив бесконечность слева и справа:
    int n; cin >> n;
    vector<int> a(1+n+1, inf);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // посчитаем количество долин
    int cnt = 0;
    for (int L = 1, R; L <= n; L = R) {
        // найдём полуинтервал [L, R) состоящий из равных элементов
        for (R = L; R <= n && a[R] == a[L]; R++);
        // проверим, является ли он долиной
        // нужно, чтобы по бокам были строго бОльшие элементы
        if (a[L-1] > a[L] && a[L] < a[R])
            cnt++;
    }
    cout << (cnt == 1 ? "YES" : "NO") << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
