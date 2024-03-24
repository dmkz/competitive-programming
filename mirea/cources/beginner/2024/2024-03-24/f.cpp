#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
void solve() {
    // читаем данные и считаем изначальную величину ряда
    // и запоминаем на сколько изменится сумма если мы поменяем i-й элемент
    int n; cin >> n;
    ll sum = 0;
    string s; cin >> s;
    vector<int> change(n);
    for (int i = 0; i < n; i++) {
        int seeLeft = i;
        int seeRight = n - i - 1;
        int curr = ((s[i] == 'L') ? seeLeft : seeRight);
        sum += curr;
        // на сколько изменится сумма, если мы поменяем этот элемент?
        if (s[i] == 'L')
            change[i] = seeRight-seeLeft;
        else
            change[i] = seeLeft-seeRight;
    }
    // теперь будем менять только самые прибыльные элементы, то есть
    // сортируем вектор change по убыванию
    sort(all(change), greater<>());
    ll maxSum = sum;
    for (auto it : change) {
        sum += it;
        maxSum = max(maxSum, sum);
        cout << maxSum << ' ';
    }
    cout << '\n';
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
