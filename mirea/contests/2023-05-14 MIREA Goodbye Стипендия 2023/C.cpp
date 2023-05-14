#include <bits/stdc++.h>
using namespace std;
int main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем запросы и отвечаем на них:
    int tt; cin >> tt;
    while (tt --> 0) {
        long long m, k;
        cin >> m >> k;
        if (m < k) { // совсем невозможный вариант
            cout << "-1\n";
            continue;
        }
        // максимальное число это m / k
        // минимальное это максимальное для k+1 + 1, то есть m / (k+1) + 1
        long long max = m / k;
        if (m / max != k) {
            cout << "-1\n";
            continue;
        }
        long long min = m / (k+1) + 1;
        cout << min << ' ' << max << '\n';
    }
    return 0;
}
