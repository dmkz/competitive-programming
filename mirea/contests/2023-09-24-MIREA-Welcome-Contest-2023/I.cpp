#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int tt; cin >> tt;
    while (tt --> 0) {
        int t1, t2; double R;
        cin >> t1 >> t2 >> R;
        // расстояние линейно зависит от радиуса
        // dist(R) = R * dist(1)
        // копируем-вставляем dist(1) из первого примера, получаем ответ
        cout << (t2 - t1) * R * 6.362265131567 << endl;
    }
}