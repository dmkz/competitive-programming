#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
void solve() {
    int n, s; cin >> n >> s;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // нужно найти отрезок из 0 и 1 такой что сумма на нём равна s
    // воспользуемся методом двух указателей, поддерживая сумму на отрезке
    int L = 0, R = 0, currSum = 0;
    int answ = inf;
    while (L < n) {
        // сдвигаем правую границу пока сумма не станет больше 's'
        while (R < n && (currSum + a[R] <= s))
            currSum += a[R++];
        // на полуинтервале [L, R) сумма == s
        // если это не так, то массив давно уже кончился
        if (currSum == s)
            answ = min(answ, n - (R - L));
        // сдвигаем левую границу
        currSum -= a[L++];
    }
    // выводим ответ:
    if (answ == inf)
        answ = -1;
    cout << answ << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
