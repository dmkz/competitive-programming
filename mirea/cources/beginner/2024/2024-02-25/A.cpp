#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем n как строку:
    string n; cin >> n;
    // пробегаемся по всем разрядам. Надо для каждого ненулевого разряда вывести
    // соответствующее ему число. Всё делаем при помощи операций со строками
    vector<string> answer;
    const int nDigits = (int)n.size();
    for (int i = 0; i < nDigits; i++)
        if (n[i] != '0') {
            const int currNumberLen = nDigits - i;
            string number(currNumberLen, '0');
            number[0] = n[i];
            answer.push_back(number);
        }
    // выводим ответ:
    cout << answer.size() << "\n";
    for (const auto &number : answer)
        cout << number << ' ';
    cout << "\n";
}
main() {
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
