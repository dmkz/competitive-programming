// Решим задачу бинарным поиском по стороне квадрата. Если мы знаем сторону, то знаем и
// площадь. В квадрате чёрных и белых клеток примерно поровну. Для нечётной длины чёрных
// клеток на 1 больше, чем белых, поэтому, если k - сторона квадрата, то точная формула
// для количества чёрных клеток равна (k^2+1)/2. Условие того, что сторона нам подходит:
// (k^2+1)/2 <= n. Ищем ответ на полуинтервале [0, 2*10^9).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// Функция проверки: можем ли мы получить квадрат со стороной side?
bool check(ll side, ll n) {
    // чёрных и белых квадратов примерно поровну, около половины:
    ll square = side * side;
    ll white = square / 2;
    ll black = square - white;
    return black <= n;
}
void solve() {
    ll n; cin >> n;
    ll low = 0, high = 2e9L;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (check(mid, n)) low = mid;
        else high = mid;
    }
    cout << low << '\n';
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
