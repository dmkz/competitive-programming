#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // каждой закрывающей скобке будем сопоставлять крайнюю открывающую скобку
    // если такой скобки нет, то пропускаем закрывающую скобку
    string s; cin >> s;
    int balance = 0, answ = 0;
    for (auto it : s) {
        if (it == '(')
            balance++;
        else if (balance > 0) {
            answ += 2;
            balance--;
        }
    }
    cout << answ << endl;
}
