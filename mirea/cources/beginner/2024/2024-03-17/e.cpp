#include <bits/stdc++.h>
using namespace std;
void solve() {
    // прочитаем данные, записав в ячейку [h][w] площадь прямоугольников
    vector s(1024, vector(1024, 0LL));
    int n, q; cin >> n >> q;
    while (n --> 0) {
        int h, w; cin >> h >> w;
        s[h][w] += h * w;
    }
    // посчитаем двумерные префикс-суммы:
    for (int r = 1; r < 1024; r++)
        for (int c = 1; c < 1024; c++)
            s[r][c] += s[r-1][c] + s[r][c-1] - s[r-1][c-1];
    // ответим на запросы суммы в прямоугольнике:
    while (q --> 0) {
        int h1, w1, h2, w2;
        cin >> h1 >> w1 >> h2 >> w2;
        h2--, w2--;
        cout << s[h2][w2] - s[h1][w2] - s[h2][w1] + s[h1][w1] << "\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
