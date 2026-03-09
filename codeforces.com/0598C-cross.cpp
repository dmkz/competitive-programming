// геометрия, сортировка по полярному углу, минимальный угол между векторами
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
using tiii = tuple<int,int,int>;
struct Frac { ll p, q; };
bool operator<(const Frac &a, const Frac &b) {
    bool signA = (a.p >= 0);
    bool signB = (b.p >= 0);
    if (signA != signB)
        return signA < signB;
    __int128 lhs = (__int128)a.p * a.p * b.q;
    __int128 rhs = (__int128)b.p * b.p * a.q;
    if (signA)
        return lhs < rhs;
    else
        return lhs > rhs;
}
bool operator>(const Frac &a, const Frac &b) {
    return b < a;
}
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
    // сортируем по полярному углу в целых числах через векторное произведение:
    sort(all(a), [](const auto &lhs, const auto &rhs){
        auto half = [](int x, int y) {
            return (y > 0 || (y == 0 && x > 0));
        };
        auto [x1, y1, id1] = lhs;
        auto [x2, y2, id2] = rhs;
        bool h1 = half(x1, y1);
        bool h2 = half(x2, y2);
        if (h1 != h2)
            return h1 > h2;
        return 1LL * x1 * y2 - 1LL * y1 * x2 > 0;
    });
    // ищем лучший ответ:
    auto getAngle = [&](int i){
        auto [x1,y1,id1] = a[i];
        auto [x2,y2,id2] = a[(i+1)%n];
        // угол между двумя векторами через acos:
        auto p = x1*1LL*x2+y1*1LL*y2;
        auto q1 = x1*1LL*x1+y1*1LL*y1;
        auto q2 = x2*1LL*x2+y2*1LL*y2;
        return make_tuple(Frac{p,q1*q2}, id1, id2);
    };
    auto answ = getAngle(0);
    for (int i = 1; i < n; i++)
        answ = max(answ, getAngle(i));
    // выводим ответ:
    auto [_, i, j] = answ;
    cout << i << ' ' << j << endl;
}
