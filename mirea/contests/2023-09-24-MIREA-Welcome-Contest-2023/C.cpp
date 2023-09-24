#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// ответы для одной грани:
// 3, 9, 18, 30
// 3 + 6 + 9 + 12 + ...
// 3 * (1 + 2 + ... n)
ll s(ll n) {
// функция считает число спичек на одной грани
    return 3 * n * (n + 1) / 2;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        ll n; cin >> n;
        // 4 грани вычесть шесть рёбер, посчитанных дважды
        cout << 4 * s(n) - 6 * n << endl;
    }
}