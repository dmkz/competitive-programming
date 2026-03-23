// жадные алгоритмы, сортировка строк, лексикографически наименьшая конкатенация
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем строки
    int n; cin >> n;
    vector<string> a(n);
    for (auto &it : a)
        cin >> it;
    // сортируем их жадным компаратором:
    stable_sort(a.begin(), a.end(), [](const string &ai, const string &aj){
        return ai + aj < aj + ai;
    });
    // выводим ответ:
    for (const auto &it : a)
        cout << it;
    cout << '\n';
}
