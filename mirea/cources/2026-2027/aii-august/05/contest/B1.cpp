#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные:
    int n, m; cin >> n >> m;
    // находим их НОД: он содержит все общие простые делители
    int g = gcd(n, m);
    // раскладываем их НОД на простые множители:
    vector<int> p;
    for (int i = 2; i * i <= g; i++)
        if (g % i == 0) {
            p.push_back(i);
            do { g /= i; } while (g % i == 0);
        }
    if (g > 1)
        p.push_back(g);
    // сокращаем числа n и m на их общие простые:
    for (int pi : p) {
        while (n % pi == 0) n /= pi;
        while (m % pi == 0) m /= pi;
    }
    // выводим ответ (через пробел, чтобы проверить, принимает ли Codeforces такой формат):
    if (n > m) cout << "Nikita ";
    else if (n < m) cout << "Misha ";
    else cout << "Friendship ";
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
