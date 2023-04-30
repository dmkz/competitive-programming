#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные и считаем сколько книг каждого типа:
    int n, m; cin >> n >> m;
    vector<int> cnt(1+m);
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        cnt[a]++;
    }
    // считаем ответ. pref - сумма кол-ва книг каждого типа на префиксе
    // к ответу добавляется cnt[j] * (cnt[j-1] + cnt[j-2] + ... + cnt[1]);
    int answ{}, pref{};
    for (int i = 1; i <= m; i++) {
        answ += pref * cnt[i];
        pref += cnt[i];
    }
    cout << answ << endl;
}
