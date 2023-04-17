#include <bits/stdc++.h>
using namespace std;
bool isSubstring(const string &sub, const string &s) {
    return s.find(sub) != s.npos;
}
int main() {
    int n; cin >> n;
    vector<string> a(n);
    for (auto &it : a)
        cin >> it;
    // отсортировать по длине:
    stable_sort(a.begin(), a.end(), [](const string &fi, const string &se) {
        return fi.size() < se.size();
    });
    // проверить, что всё зашибись:
    bool ok = true;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            ok &= isSubstring(a[i],a[j]);
    // вывести ответ:
    if(!ok) cout << "NO\n";
    else {
        cout << "YES\n";
        for (auto &it : a)
            cout << it << '\n';
    }
}