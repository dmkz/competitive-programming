// геометрия, сортировка по полярному углу, минимальный угол между векторами
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ld = long double;
const ld pi = acos(-1.0L);
using tiii = tuple<int,int,int>;
main() {
    // читаем векторы и сохраняем тройки {x, y, id}:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<tiii> a(n);
    for (int i = 0; i < n; i++) {
        auto &[x, y, id] = a[i];
        cin >> x >> y;
        id = i+1;
    }
    // сортируем по полярному углу: atan2(y, x) возвращает угол в (-pi, pi]:
    sort(all(a), [](const auto &lhs, const auto &rhs){
        auto [x1,y1,id1] = lhs;
        auto [x2,y2,id2] = rhs;
        return atan2l(y1,x1) < atan2l(y2,x2);
    });
    // ищем минимальный ответ:
    auto answ = make_tuple(2*pi,-1,-1);
    for (int i = 0; i < n; i++) {
        auto [x1,y1,id1] = a[i];
        auto [x2,y2,id2] = a[(i+1)%n];
        // угол между двумя векторами: min(|a1-a2|, 2*pi-|a1-a2|)
        ld angle1 = atan2l(y1,x1);
        ld angle2 = atan2l(y2,x2);
        ld diff = abs(angle1 - angle2);
        if (diff > pi)
            diff = 2 * pi - diff;
        answ = min(answ, make_tuple(diff, id1, id2));
    }
    // выводим ответ:
    auto [_, i, j] = answ;
    cout << i << ' ' << j << endl;
}
