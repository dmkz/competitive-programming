#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные и сортируем их по убыванию:
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    sort(all(a), greater<>());
    // будем посещать k максимумов. Переберём каждый вариант и выберем лучший:
    int64_t sum = 0, answ = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        sum -= (i+1);
        if (sum >= 0)
            setmax(answ, sum);
    }
    cout << answ << endl;
}
