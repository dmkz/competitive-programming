// полярный угол, сортировка, инверсии, ordered_set
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using Real = long double;
// подключаем ordered_set!
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag, tree_order_statistics_node_update>;
// set.find_by_order(k); <-- найти k-й элемент (порядковая статистика)
// set.order_of_key(x); <-- сколько элементов меньше чем x
using prr = pair<Real,Real>;
// функция readReal() читает и возвращает вещественное число:
Real readReal() {
    string s; cin >> s;
    return stold(s);
}
main() {
    // чтение данных:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int R, K; cin >> R >> K;
    int N; cin >> N;
    vector<pair<prr,prr>> segments(N);
    for (auto &[A, B] : segments) {
        A.first = readReal();
        A.second = readReal();
        B.first = readReal();
        B.second = readReal();
    }
    // сортировка по полярному углу:
    sort(all(segments), [](const auto &lhs, const auto &rhs){
        auto ang = [](Real x, Real y){
            const Real PI = acosl(-1.0L);
            Real a = atan2l(y, x);
            if (a > PI/2) a -= 2*PI; // (-pi,pi] -> [-3pi/2, pi/2]
            return a;
        };
        const auto [x1,y1] = lhs.first;
        const auto [x2,y2] = rhs.first;
        return ang(x1,y1) < ang(x2,y2);
    });
    // подсчёт числа пересечений:
    ordered_set<Real> s;
    int64_t answ{};
    for (const auto &[_, P] : segments) {
        auto [x2, y2] = P;
        answ += s.size() - s.order_of_key(x2);
        s.insert(x2);
    }
    cout << answ << '\n';
}
