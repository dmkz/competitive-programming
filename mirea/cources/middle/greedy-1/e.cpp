#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<string> a(n);
    for (auto &it : a)
        cin >> it;
    // компаратор: будем переставлять две подстроки, если это принесёт пользу
    // посортим строки по этому компаратору и выведем ответ
    sort(a.begin(), a.end(), [](const auto &fi, const auto &se) {
        return fi + se < se + fi;
    });
    string res;
    for (auto &it : a)
        res += it;
    cout << res << endl;
}
