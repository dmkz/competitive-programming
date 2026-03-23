// геометрия, количество параллелограммов
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем точки:
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    // Диагонали параллелограмма пересекаются и точкой пересечения делятся пополам.
    // Этого достаточно, чтобы фигура называлась параллелограммом.
    // Рассмотрим середины диагоналей. Требуется для каждой середины выбрать
    // две различные диагонали.
    map<pair<int, int>, int64_t> count;
    int64_t ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            ans += count[{x[i]+x[j], y[i]+y[j]}]++;
    cout << ans << '\n';
}
