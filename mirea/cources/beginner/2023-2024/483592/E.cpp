#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // рассмотрим какой-то один цвет. для него мы не сможем изменить порядок
    // то есть если для одного цвета сортированность не выполняется, то никак
    // не посортить, так как запрещено менять местами элементы одного цвета
    // иначе всегда есть способ посортить
    
    // читаем данные и собираем значения элементов по цветам:
    int n; cin >> n;
    map<int, vector<int>> values;
    // values[цвет] = вектор значений элементов этого цвета
    for (int i = 0, a, c; i < n; i++) {
        cin >> a >> c;
        values[c].push_back(a);
    }
    // проверяем на отсортированность:
    bool ok = 1;
    for (const auto &[_, arr] : values)
        ok &= is_sorted(arr.begin(), arr.end());
    cout << (ok ? "YES" : "NO") << endl;
}
 
