// префикс-суммы, комбинаторика, O(n log(n))
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // заменяем "a" на "+1", b - на "-1", и считаем префикс-суммы:
    int n; cin >> n;
    string s; cin >> s;
    vector<int> pref{0};
    for (auto c : s)
        pref.push_back(pref.back() + (c == 'a' ? +1 : -1));
    // требуется посчитать кол-во подотрезков [L, R], сумма на которых
    // равна нулю: pref[R+1] == pref[L].
    // считаем кол-во каждого элемента:
    map<int, int> cnt;
    for (auto item : pref)
        cnt[item]++;
    // считаем ответ:
    int64_t answ{};
    for (const auto &[_, k] : cnt)
        answ += k * (k - 1LL) / 2;
    cout << answ << endl;
}
