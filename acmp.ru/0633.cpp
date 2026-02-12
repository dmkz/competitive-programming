// строки, сортировка
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string team;
    getline(cin, team);
    vector<string> a(3);
    for (auto &it : a)
        getline(cin, it);
    sort(a.begin(), a.end());
    cout << team << ":";
    for (int i = 0; i < 3; i++) {
        if (i > 0) cout << ",";
        cout << " " << a[i];
    }
    cout << endl;
}
