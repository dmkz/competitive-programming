#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    auto answ = 0LL;
    for (int i = 1; i < n; i++)
        // прибавляем полусумму оснований на высоту, но сразу удваиваем
        // не забываем приводить к типу лонг лонг
        answ += (x[i] - x[i-1] + 0LL) * (y[i] + y[i-1]);
    cout << answ << endl;
}
