#include <iostream>
#include <vector>
#include <set>
using namespace std;
using tiii = tuple<int,int,int>;
using vtiii = vector<tiii>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int,int>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
int main() {
    // читаем данные. будем делать сканлайн для каждого бита отдельно
    // если бит должен быть равен 1, то мы должны от L до R выставить
    // все единицы. Если бит должен быть равен 0, то проверим, что
    // на отрезке от L до R есть хотя бы один ноль - префикс-суммами
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vi a(n);
    vvi add(30, vi(n+1));
    vvpii check(30);
    vtiii queries(m);
    for (auto &[l, r, q] : queries) {
        cin >> l >> r >> q;
        l--, r--;
        for (int bit = 0; bit < 30; bit++) {
            if ((q >> bit) & 1)
                add[bit][l]++, add[bit][r+1]--;
            else
                check[bit].emplace_back(l, r);
        }
    }
    bool ok = 1;
    for (int bit = 0; ok && bit < 30; bit++) {
        // рассматриваем бит #bit. Сначала выставим единицы:
        int bal = 0;
        vi sum(n);
        for (int i = 0; i < n; i++) {
            bal += add[bit][i];
            if (bal > 0) {
                a[i] |= (1 << bit);
                sum[i]++;
            }
            if (i > 0)
                sum[i] += sum[i-1];
        }
        // теперь проверим нули:
        for (auto &[l, r] : check[bit]) {
            int cnt1 = sum[r] - (l-1>=0?sum[l-1]:0);
            if (cnt1 == (r-l+1))  { // все единицы
                ok = false;
                break;
            }
        }
    }
    if (ok) {
        cout << "YES\n";
        for (auto it : a)
            cout << it << ' ';
        cout << endl;
    } else {
        cout << "NO\n";
    }
}