#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    int64_t answ{};
    // две последние цифры должны делиться на 4
    for (int i = 0; i + 1 < (int)s.size(); i++)
        if (stoi(s.substr(i, 2)) % 4 == 0)
            answ += (i + 1);
    // либо это подстрока длины 1, которая сама делится на 4:
    for (int i = 0; i < (int)s.size(); i++)
        if ((s[i] - '0') % 4 == 0)
            answ++;
    cout << answ << '\n';
}
