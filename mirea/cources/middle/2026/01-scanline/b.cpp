#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using vl = vector<ll>;
bool check(vl a, int n, ll m, int w, ll mid) {
    // проверка, сможем ли мы сделать все кусты высотой >= mid???
    vl inc(n+w+1);
    ll balance = 0;
    for (int i = 0; i < n && m >= 0; i++) {
        balance += inc[i];
        ll item = a[i] + balance;
        ll delta = max<ll>(0, mid - item); // сколько не хватает
        // поливаем отрезок [i, i + w) delta раз:
        m -= delta;
        inc[i+w] -= delta;
        balance += delta;
    }
    return m >= 0; // хватило операций
}
int main() {
    // читаем исходные данные:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, w;
    cin >> n >> m >> w;
    vl a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // бинарный поиск по ответу - минимальной высоте куста
    ll low = 0, high = 2e9;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        // сможем сделать все кусты высотой >= mid???
        if (check(a, n, m, w, mid)) low = mid;
        else high = mid;
    }
    cout << low << endl;
}