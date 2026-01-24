#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using tiii = tuple<int,int,int>;
using vtiii = vector<tiii>;
using vi = vector<int>;
using vl = vector<ll>;
int main() {
    // читаем данные и операции
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vl a(n+1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vtiii ops(m);
    for (auto &[l, r, d] : ops) {
        cin >> l >> r >> d;
        l--, r--;
    }
    // cntOps[i] = сколько раз должны применить i-ю операцию
    // прочитаем запросы и обработаем прибавление на [l,r]
    // в массиве cntOps через сканлайн
    vi cntOps(m+1);
    while (k --> 0) {
        int l, r; cin >> l >> r;
        l--, r--;
        cntOps[l]++;
        cntOps[r+1]--;
    }
    // второй сканлайн: для прибавлений на отрезке [l,r] в массиве a
    ll balance = 0;
    vl inc(n+1);
    for (int i = 0; i < m; i++) {
        balance += cntOps[i];
        auto [l,r,d]=ops[i];
        inc[l] += d * balance;
        inc[r+1] -= d * balance;
    }
    balance = 0;
    for (int i = 0; i < n; i++) {
        balance += inc[i];
        a[i] += balance;
    }
    // выводим ответ
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
}