#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем проходимость и значения клеток:
    int n, m; cin >> n >> m;
    vector<string> cells(n);
    for (auto& it : cells)
        cin >> it;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (auto& row : a)
        for (auto& it : row)
            cin >> it;
    // previous хранит значения для строки над текущей, а current формируется для текущей строки.
    const ll inf = 1LL << 60;
    vector<ll> previous(m, -inf), current(m);
    for (int i = 0; i < n; i++) {
        // Обработку новой строки начинаем с недостижимых состояний.
        fill(current.begin(), current.end(), -inf);
        for (int j = 0; j < m; j++) {
            // Через закрытую клетку путь пройти не может.
            if (cells[i][j] == '#') continue;
            // Верхняя левая клетка служит началом любого пути.
            if (i == 0 && j == 0) current[j] = a[i][j];
            else {
                // Выбираем лучший из путей, которые приходят сверху или слева.
                ll best = max(previous[j], j == 0 ? -inf : current[j - 1]);
                // Значение для клетки можно получить только от достижимого предшественника.
                if (best != -inf) current[j] = best + a[i][j];
            }
        }
        // После обработки эта строка станет предыдущей для следующей.
        swap(previous, current);
    }
    if (previous[m - 1] == -inf) cout << "IMPOSSIBLE\n";
    else cout << previous[m - 1] << '\n';
}