#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
// функция, которая считает минимальный префиксный баланс и суммарный баланс для
// скобочной последовательности. возвращает пару из этих величин
auto findPrefAndBal(const string &s) {
    int minPref = 0, bal = 0;
    for (auto it : s) {
        if (it == '(') bal++;
        else bal--;
        minPref = min(minPref, bal);
    }
    return pii(minPref, bal);
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    map<int, int> cnt; // для каждого баланса храним количество строк
    vector<pii> rights; // все доступные пары (мин.преф, баланс)
    for (int i = 0; i < n; i++) {
        // читаем строку
        string s; cin >> s;
        // считаем её характеристики
        auto [minPref, balance] = findPrefAndBal(s);
        // если мин.префикс >= 0, то её можно использовать как левую часть:
        if (minPref >= 0)
            cnt[balance]++;
        // складываем как кандидата на правую часть:
        rights.emplace_back(minPref, balance);
    }
    // считаем ответ
    int64_t answ{};
    for (const auto &[minPref, balance] : rights) {
        // текущий кандидат на правую часть
        // условие на левую часть:
        // leftBalance >= -minPref
        // условие на итог:
        // leftBalance + balance == 0
        int leftBalance = -balance;
        if (leftBalance < -minPref)
            continue;
        answ += cnt[leftBalance];
    }
    cout << answ << endl;
}
