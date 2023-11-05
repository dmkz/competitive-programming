#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // надо удалить ближайший символ, который меньше своего соседа справа
    // если такого нет, то удалить последний символ в строке
    string s; cin >> s;
    int pos = 0;
    while (pos + 1 < (int)s.size() && s[pos] >= s[pos+1])
        pos++;
    s.erase(pos, 1);
    cout << s << endl;
}
