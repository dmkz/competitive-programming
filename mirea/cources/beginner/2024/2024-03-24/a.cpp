#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // ответ: кол-во различных букв + n
    int n; cin >> n;
    string s; cin >> s;
    sort(all(s));
    s.erase(unique(all(s)), s.end());
    cout << s.size() + n << "\n";
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
