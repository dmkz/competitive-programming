#include <bits/stdc++.h>
using namespace std;
void setmin(auto &x, const auto &y) {
    if (y < x)
        x = y;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных:
    int xs, ys; cin >> xs >> ys;
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    // функция расстояния между двумя точками:
    auto distBetween = [&](int i, int j) {
        int dx = x[i] - x[j];
        int dy = y[i] - y[j];
        return dx * dx + dy * dy;
    };
    // функция расстояния между стартовой и i-й точками:
    auto distTo = [&](int i) {
        int dx = x[i] - xs;
        int dy = y[i] - ys;
        return dx * dx + dy * dy;
    };
    // считаем минимальное расстояние, за которое можем собрать
    // всё множество вещей: {расстояние, индекс 1-й вещи, индекс 2-й вещи}
    vector<tuple<int64_t, int, int>> dist(1 << n, {LLONG_MAX, -1, -1});
    dist[0] = {0, -1, -1};
    for (int subset = 1; subset < (1 << n); subset++) {
        // старший единичный разряд - эту вещь мы несём:
        int a = __lg(subset);
        // несём только её:
        setmin(dist[subset], make_tuple(2 * distTo(a) + get<0>(dist[subset ^ (1 << a)]), a, -1));
        // берём к ней в пару кого-то:
        for (int b = 0; b < a; b++)
            if ((subset >> b) & 1) {
                int64_t curr = distTo(a); // идём в "a"
                curr += distBetween(a, b); // переходим в "b"
                curr += distTo(b); // возвращаемся из "b"
                curr += get<0>(dist[subset ^ (1 << a) ^ (1 << b)]); // собираем оставшиеся
                setmin(dist[subset], make_tuple(curr, a, b));
            }
    }
    // выводим ответ:
    int subset = (1 << n) - 1;
    cout << get<0>(dist[subset]) << endl;
    vector<int> path = {0};
    while (subset > 0) {
        auto [_, a, b] = dist[subset];
        if (b == -1) {
            // берём одну вещь
            subset ^= (1 << a);
            path.push_back(a+1);
            path.push_back(0);
        } else {
            // берём две вещи
            subset ^= (1 << a);
            subset ^= (1 << b);
            path.push_back(a+1);
            path.push_back(b+1);
            path.push_back(0);
        }
    }
    for (auto it : path)
        cout << it << ' ';
    cout << endl;
}
