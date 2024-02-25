#include <bits/stdc++.h>
using namespace std;
void solve() {
    // для начала посчитаем все строки
    int n; cin >> n;
    map<string, int> count;
    while (n --> 0) {
        string s; cin >> s;
        count[s]++;
    }
    // просто переберём все 2*k*k*(k-1)/2 различных пар строк (a, b)
    // различающихся в одной букве, где k - размер алфавита
    int64_t answer = 0;
    for (int differencePos = 0; differencePos < 2; differencePos++)
        for (char sameLetter = 'a'; sameLetter <= 'k'; sameLetter++)
            for (char diffLetter1 = 'a'; diffLetter1 <= 'k'; diffLetter1++)
                for (char diffLetter2 = diffLetter1+1; diffLetter2 <= 'k'; diffLetter2++) {
                    // строим строки текущей пары (a, b)
                    string a(2, sameLetter), b(2, sameLetter);
                    a[differencePos] = diffLetter1;
                    b[differencePos] = diffLetter2;
                    // прибавляем кол-во пар
                    answer += count[a] * 1LL * count[b];
                }
    // выводим ответ:
    cout << answer << "\n";
}
main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // мультитесты
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
