#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // алфавит состоит из 26 букв, поэтому мы всегда можем выбрать букву,
    // не совпадающую с соседями
    // итерируемся по тройкам соседей (i-1, i, i+1) и заменяем букву посередине,
    // если s[i] == s[i-1]. Замену делаем на символ, не совпадающий ни с i-1, ни с i+1
    string s; cin >> s;
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i-1] == s[i]) {
            char c1 = s[i-1];
            char c2 = i+1 < (int)s.size() ? s[i+1] : '?';
            // выбираем любой символ, который не совпадает с этими двумя
            for (int c = 'a'; c <= 'z'; ++c) {
                if (c != c1 && c != c2) {
                    s[i] = c;
                    break;
                }
            }
        }
    }
    // выводим ответ
    cout << s;
    return 0;
}